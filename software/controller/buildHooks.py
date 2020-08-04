#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# pylint: disable=undefined-variable
import os
import shutil
Import("env", "projenv")

deviceVID  = "0x08de"
devicePID  = "0xbabe"
deviceName = "Ben KeyController"

# Edit USB device information
def editUSBsettings(fileName):
    # Search and replace inside the file
    fHandler = open(fileName, "rt")
    data = fHandler.read()
    data = data.replace("0x16C0", deviceVID)                            # Replace all occurrences of the original Vendor  ID (VID)
    data = data.replace("0x0482", devicePID)                            # Replace all occurrences of the original Product ID (PID)
    data = data.replace("Teensy Keyboard/Mouse/Joystick", deviceName)   # Replace all occurrences of the original Device  Name
    fHandler.close()
    # Reopen the input file in write mode
    fHandler = open(fileName, "wt")
    #overrite the input file with the resulting data
    fHandler.write(data)
    #close the file
    fHandler.close()

# Move back the original file
def buildPostAction(source, target, env):
    shutil.move(fileNameBackup, fileName)


# Before compilation (BEGIN)
print("----------------------------------------------- Compilation setup [BEGIN]")
# usb_private.h backup
fileName = os.path.sep.join([env['CPPPATH'][1]]+["usb_hid","usb_private.h"])
fileNameBackup = fileName+".backup"
shutil.copyfile(fileName, fileNameBackup)
editUSBsettings(fileName)
print("----------------------------------------------- Compilation setup [ END ]")



env.AddPostAction("buildprog", buildPostAction)
