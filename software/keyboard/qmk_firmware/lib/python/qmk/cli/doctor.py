"""QMK Doctor

Check out the user's QMK environment and make sure it's ready to compile.
"""
import platform
import re
import shutil
import subprocess
from pathlib import Path

from milc import cli
from qmk import submodules
from qmk.questions import yesno
from qmk.commands import run

ESSENTIAL_BINARIES = {
    'dfu-programmer': {},
    'avrdude': {},
    'dfu-util': {},
    'avr-gcc': {
        'version_arg': '-dumpversion'
    },
    'arm-none-eabi-gcc': {
        'version_arg': '-dumpversion'
    },
    'bin/qmk': {},
}


def _udev_rule(vid, pid=None, *args):
    """ Helper function that return udev rules
    """
    rule = ""
    if pid:
        rule = 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", ATTRS{idProduct}=="%s", TAG+="uaccess", RUN{builtin}+="uaccess"' % (vid, pid)
    else:
        rule = 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", TAG+="uaccess", RUN{builtin}+="uaccess"' % vid
    if args:
        rule = ', '.join([rule, *args])
    return rule


def _deprecated_udev_rule(vid, pid=None):
    """ Helper function that return udev rules

    Note: these are no longer the recommended rules, this is just used to check for them
    """
    if pid:
        return 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", ATTRS{idProduct}=="%s", MODE:="0666"' % (vid, pid)
    else:
        return 'SUBSYSTEMS=="usb", ATTRS{idVendor}=="%s", MODE:="0666"' % vid


def parse_gcc_version(version):
    m = re.match(r"(\d+)(?:\.(\d+))?(?:\.(\d+))?", version)

    return {
        'major': int(m.group(1)),
        'minor': int(m.group(2)) if m.group(2) else 0,
        'patch': int(m.group(3)) if m.group(3) else 0
    }


def check_arm_gcc_version():
    """Returns True if the arm-none-eabi-gcc version is not known to cause problems.
    """
    if 'output' in ESSENTIAL_BINARIES['arm-none-eabi-gcc']:
        version_number = ESSENTIAL_BINARIES['arm-none-eabi-gcc']['output'].strip()
        cli.log.info('Found arm-none-eabi-gcc version %s', version_number)

    return True  # Right now all known arm versions are ok


def check_avr_gcc_version():
    """Returns True if the avr-gcc version is not known to cause problems.
    """
    if 'output' in ESSENTIAL_BINARIES['avr-gcc']:
        version_number = ESSENTIAL_BINARIES['avr-gcc']['output'].strip()

        parsed_version = parse_gcc_version(version_number)
        if parsed_version['major'] > 8:
            cli.log.error('We do not recommend avr-gcc newer than 8. Downgrading to 8.x is recommended.')
            return False

        cli.log.info('Found avr-gcc version %s', version_number)
        return True

    return False


def check_avrdude_version():
    if 'output' in ESSENTIAL_BINARIES['avrdude']:
        last_line = ESSENTIAL_BINARIES['avrdude']['output'].split('\n')[-2]
        version_number = last_line.split()[2][:-1]
        cli.log.info('Found avrdude version %s', version_number)

    return True


def check_dfu_util_version():
    if 'output' in ESSENTIAL_BINARIES['dfu-util']:
        first_line = ESSENTIAL_BINARIES['dfu-util']['output'].split('\n')[0]
        version_number = first_line.split()[1]
        cli.log.info('Found dfu-util version %s', version_number)

    return True


def check_dfu_programmer_version():
    if 'output' in ESSENTIAL_BINARIES['dfu-programmer']:
        first_line = ESSENTIAL_BINARIES['dfu-programmer']['output'].split('\n')[0]
        version_number = first_line.split()[1]
        cli.log.info('Found dfu-programmer version %s', version_number)

    return True


def check_binaries():
    """Iterates through ESSENTIAL_BINARIES and tests them.
    """
    ok = True

    for binary in sorted(ESSENTIAL_BINARIES):
        if not is_executable(binary):
            ok = False

    return ok


def check_submodules():
    """Iterates through all submodules to make sure they're cloned and up to date.
    """
    ok = True

    for submodule in submodules.status().values():
        if submodule['status'] is None:
            cli.log.error('Submodule %s has not yet been cloned!', submodule['name'])
            ok = False
        elif not submodule['status']:
            cli.log.error('Submodule %s is not up to date!', submodule['name'])
            ok = False

    return ok


def check_udev_rules():
    """Make sure the udev rules look good.
    """
    ok = True
    udev_dir = Path("/etc/udev/rules.d/")
    desired_rules = {
        'dfu': {_udev_rule("03eb", "2ff4"), _udev_rule("03eb", "2ffb"), _udev_rule("03eb", "2ff0")},
        'input_club': {_udev_rule("1c11", "b007")},
        'stm32': {_udev_rule("1eaf", "0003"), _udev_rule("0483", "df11")},
        'bootloadhid': {_udev_rule("16c0", "05df")},
        'caterina': {
            _udev_rule("2341", "0036", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),
            _udev_rule("1b4f", "9205", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),
            _udev_rule("1b4f", "9203", 'ENV{ID_MM_DEVICE_IGNORE}="1"'),
            _udev_rule("2a03", "0036", 'ENV{ID_MM_DEVICE_IGNORE}="1"')
        }
    }

    # These rules are no longer recommended, only use them to check for their presence.
    deprecated_rules = {
        'dfu': {_deprecated_udev_rule("03eb", "2ff4"), _deprecated_udev_rule("03eb", "2ffb"), _deprecated_udev_rule("03eb", "2ff0")},
        'input_club': {_deprecated_udev_rule("1c11")},
        'stm32': {_deprecated_udev_rule("1eaf", "0003"), _deprecated_udev_rule("0483", "df11")},
        'bootloadhid': {_deprecated_udev_rule("16c0", "05df")},
        'caterina': {'ATTRS{idVendor}=="2a03", ENV{ID_MM_DEVICE_IGNORE}="1"', 'ATTRS{idVendor}=="2341", ENV{ID_MM_DEVICE_IGNORE}="1"'}
    }

    if udev_dir.exists():
        udev_rules = [rule_file for rule_file in udev_dir.glob('*.rules')]
        current_rules = set()

        # Collect all rules from the config files
        for rule_file in udev_rules:
            for line in rule_file.read_text().split('\n'):
                line = line.strip()
                if not line.startswith("#") and len(line):
                    current_rules.add(line)

        # Check if the desired rules are among the currently present rules
        for bootloader, rules in desired_rules.items():
            # For caterina, check if ModemManager is running
            if bootloader == "caterina":
                if check_modem_manager():
                    ok = False
                    cli.log.warn("{bg_yellow}Detected ModemManager without the necessary udev rules. Please either disable it or set the appropriate udev rules if you are using a Pro Micro.")
            if not rules.issubset(current_rules):
                deprecated_rule = deprecated_rules.get(bootloader)
                if deprecated_rule and deprecated_rule.issubset(current_rules):
                    cli.log.warn("{bg_yellow}Found old, deprecated udev rules for '%s' boards. The new rules on https://docs.qmk.fm/#/faq_build?id=linux-udev-rules offer better security with the same functionality.", bootloader)
                else:
                    cli.log.warn("{bg_yellow}Missing udev rules for '%s' boards. You'll need to use `sudo` in order to flash them.", bootloader)

    return ok


def check_modem_manager():
    """Returns True if ModemManager is running.
    """
    if shutil.which("systemctl"):
        mm_check = run(["systemctl", "--quiet", "is-active", "ModemManager.service"], timeout=10)
        if mm_check.returncode == 0:
            return True

    else:
        cli.log.warn("Can't find systemctl to check for ModemManager.")


def is_executable(command):
    """Returns True if command exists and can be executed.
    """
    # Make sure the command is in the path.
    res = shutil.which(command)
    if res is None:
        cli.log.error("{fg_red}Can't find %s in your path.", command)
        return False

    # Make sure the command can be executed
    version_arg = ESSENTIAL_BINARIES[command].get('version_arg', '--version')
    check = run([command, version_arg], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=5, universal_newlines=True)

    ESSENTIAL_BINARIES[command]['output'] = check.stdout

    if check.returncode in [0, 1]:  # Older versions of dfu-programmer exit 1
        cli.log.debug('Found {fg_cyan}%s', command)
        return True

    cli.log.error("{fg_red}Can't run `%s %s`", command, version_arg)
    return False


def os_test_linux():
    """Run the Linux specific tests.
    """
    cli.log.info("Detected {fg_cyan}Linux.")
    ok = True

    if not check_udev_rules():
        ok = False

    return ok


def os_test_macos():
    """Run the Mac specific tests.
    """
    cli.log.info("Detected {fg_cyan}macOS.")

    return True


def os_test_windows():
    """Run the Windows specific tests.
    """
    cli.log.info("Detected {fg_cyan}Windows.")

    return True


@cli.argument('-y', '--yes', action='store_true', arg_only=True, help='Answer yes to all questions.')
@cli.argument('-n', '--no', action='store_true', arg_only=True, help='Answer no to all questions.')
@cli.subcommand('Basic QMK environment checks')
def doctor(cli):
    """Basic QMK environment checks.

    This is currently very simple, it just checks that all the expected binaries are on your system.

    TODO(unclaimed):
        * [ ] Compile a trivial program with each compiler
    """
    cli.log.info('QMK Doctor is checking your environment.')
    ok = True

    # Determine our OS and run platform specific tests
    platform_id = platform.platform().lower()

    if 'darwin' in platform_id or 'macos' in platform_id:
        if not os_test_macos():
            ok = False
    elif 'linux' in platform_id:
        if not os_test_linux():
            ok = False
    elif 'windows' in platform_id:
        if not os_test_windows():
            ok = False
    else:
        cli.log.error('Unsupported OS detected: %s', platform_id)
        ok = False

    # Make sure the basic CLI tools we need are available and can be executed.
    bin_ok = check_binaries()

    if not bin_ok:
        if yesno('Would you like to install dependencies?', default=True):
            run(['util/qmk_install.sh'])
            bin_ok = check_binaries()

    if bin_ok:
        cli.log.info('All dependencies are installed.')
    else:
        ok = False

    # Make sure the tools are at the correct version
    for check in (check_arm_gcc_version, check_avr_gcc_version, check_avrdude_version, check_dfu_util_version, check_dfu_programmer_version):
        if not check():
            ok = False

    # Check out the QMK submodules
    sub_ok = check_submodules()

    if sub_ok:
        cli.log.info('Submodules are up to date.')
    else:
        if yesno('Would you like to clone the submodules?', default=True):
            submodules.update()
            sub_ok = check_submodules()

        if not sub_ok:
            ok = False

    # Report a summary of our findings to the user
    if ok:
        cli.log.info('{fg_green}QMK is ready to go')
    else:
        cli.log.info('{fg_yellow}Problems detected, please fix these problems before proceeding.')
        # FIXME(skullydazed/unclaimed): Link to a document about troubleshooting, or discord or something
