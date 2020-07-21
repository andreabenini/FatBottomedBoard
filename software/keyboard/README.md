# Firmware mod
Firmware for FatBottomedBoard

# Environment setup
```sh
# or use your favorite package manager to get those packages
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-newlib
```

# Project setup
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

# Copy project configuration
```sh
# Add current configuration to qmk project
cd qmk_firmare/keyboards
ln -s ../../config/fatbottomedboard .
```


## Links 
- Hints on classics layouts http://www.quadibloc.com/comp/kyb0301.htm  
- QMK Keyboard firmware builder https://kbfirmware.com/  

## Notes
QMK keyboard firmware builder is way better than TMK counterpart, use it to define wirings and create C defines
and `KEYMAP()` proper mappings. Later on you might adapt generated code to TMK firmware. Just take a look at
`kb.h` and `kb.c` generated files.  
**fatbottomedboard.json** was generated from https://kbfirmware.com/, you might use it again and return
to that site to load configuration and alter it if needed.
