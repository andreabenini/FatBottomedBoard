# Firmware mod
Firmware for FatBottomedBoard


## Setup
#### Software installation
```sh
# or use your favorite package manager to get those packages
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-newlib
```
#### Project setup
```sh
# cloning github project
git clone https://github.com/qmk/qmk_firmware
# Entering proper directory
cd qmk_firmware
# Creating submodule to start your own environment
make git-submodule
# Try to compile a basic example (optional)
make handwired/onekey/teensy_32:default
# Clean that basic example
make clean
```
#### Copy project configuration
```sh
# Add current configuration to qmk project
cd qmk_firmare/keyboards
ln -s ../../config/fatbottomedboard .
```


## Keyboard Manual
[This is up to date keyboard manual](manual.md) with keys, macros, layouts and current configuration.  
Complete keyboard layout is available in the [hardware section](../../hardware)

## Links 
- Hints on classics layouts http://www.quadibloc.com/comp/kyb0301.htm  
- QMK Keyboard firmware builder https://kbfirmware.com/  
- QMK Cheat sheet https://jayliu50.github.io/qmk-cheatsheet/
- List of unicode characters https://en.wikipedia.org/wiki/List_of_Unicode_characters


## Notes
QMK keyboard firmware builder is way better than TMK counterpart, use it to define wirings and create C defines
and `KEYMAP()` proper mappings. ~~Later on you might adapt generated code to TMK firmware.~~ Just take a look at
`kb.h` and `kb.c` generated files.  
**fatbottomedboard.json** was generated from https://kbfirmware.com/, you might use it again and return
to that site to load configuration and alter it if needed.  
[QMK](https://qmk.fm/) firmware was chosen for the project due to its cool features and good
documentation, reading docs and applying those features in a couple of hours is preferred to hacking
for weeks with an uncertain result and _(maybe)_ a 5% performance increase. **Even more:** user hooks
for custom code (here used for serial comm) with plain avr-gcc **C** code is awesome.
