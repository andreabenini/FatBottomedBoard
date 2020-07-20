#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
import os
import sys
import shutil
#vendor  id  0x08DE
#product id  0xBABE
#serial  id  0x0666

fileName            = ""
deviceVID           = "0x08DE"
devicePID           = "0xC0DE"
deviceName          = "Ben Keyboard"
deviceSerial        = "0x0666"
deviceProduct       = "benCustomKeyboard"
deviceManufacturer  = "Ben"

def Help():
    print("\n{name} usage:".format(name=sys.argv[0]))
    print("    patch - Patch QMK source code")
    print("")
    sys.exit(1)

def fileRead(fileNameToOpen):
    global fileName
    fileName = fileNameToOpen
    with open(fileName, "rt") as fHandler:
        return fHandler.read()
    print("{} read error, aborting program".format(fileName))
    sys.exit(1)

def fileWrite(data):
    global fileName
    with open(fileName, "wt") as fHandler:
        fHandler.write(data)
        fHandler.close()

def patchUSBConfig():
    data = fileRead("qmk_firmware/keyboards/kb/config.h")
    data = data.replace("0xFEED", deviceVID)                    # Vendor ID
    data = data.replace("0x6060", devicePID)                    # Product ID
    data = data.replace("qmkbuilder", deviceManufacturer)       # Manufacturer
    data = data.replace("PRODUCT         keyboard", "PRODUCT         "+deviceProduct)   # Device Product ID
    data = data.replace("DESCRIPTION     Keyboard", "DESCRIPTION     "+deviceName)      # Device Name
    fileWrite(data)

def patchMakefile():
    data = fileRead("qmk_firmware/common.mk")
    data = data.replace("files exist", "files  exist\n#Enable Unicode\nUCIS_ENABLE = yes")
    fileWrite(data)

# # TODO: Remove
# def buildPostAction(source, target, env):
#     shutil.move(fileNameBackup, fileName)
# fileName = os.path.sep.join([env['CPPPATH'][1]]+["usb_hid","usb_private.h"])
# shutil.copyfile(fileName, fileNameBackup)
def patchKeymap():
    # Copy custom keymaps
    shutil.copy("patch/keymap_unicodeBen.h", "qmk_firmware/quantum/keymap_extras/")
    # Patch keymap.c to remove warnings
    data = fileRead("qmk_firmware/keyboards/kb/keymaps/default/keymap.c")
    data = data.replace("keyevent_t event = record->event;", "// keyevent_t  event = record->event;")
    data = data.replace("RALT(KC_E)", "BK_EACUTE")
    fileWrite(data)
    # Patch kb.h to include special keymaps
    data = fileRead("qmk_firmware/keyboards/kb/kb.h")
    data = data.replace('#include "quantum.h"', '#include  "quantum.h"\n#include  "keymap_unicodeBen.h"')
    fileWrite(data)
    


# MAIN
if len(sys.argv) <= 1:
    Help()
if sys.argv[1] == "patch":
    patchUSBConfig()
    patchMakefile()
    patchKeymap()
else:
    Help()
