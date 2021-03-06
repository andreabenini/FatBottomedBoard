#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>
#include <TFT.h>

#include "main.h"
#include "data.h"
#include "defines.h"

// Display functions
void displayClear();
void displayErrorMessage(const __FlashStringHelper *errorType);
void displayRemoteConfigWaiting();

// Gauge
void displayGauge(byte *variable, byte dbPosition, byte valueMin, byte valueMax, byte valueStep, const __FlashStringHelper *measureUnit, const __FlashStringHelper *Title);

// Menu
class menuObject {
private:
    byte
        itemCount,              // Number of items in the menu
        itemPrevious,           // Previously selected item (starting from 0)
        itemCurrent,            // Currently selected item  (starting from 0)
        XStart, YStart,         // Starting X-Y positions
        YPos, YDiff,            // Current Y Pos on screen for the selected item, YDiff = difference between two elements
        PagePos,                // Page current position
        PageMax;                // Page maximum items
    void
        (*show)();
public:
    menuObject()  {}
    ~menuObject() {}
    void init(
            const __FlashStringHelper *TitleName, byte TitleXPos, byte TitleYPos,
            byte itemSelected, byte itemPageCurrent, byte itemPageMax, byte XposFirst, byte YposFirst, byte YspaceItems,
            void (*menuShow)()
    );

    void itemShow(const __FlashStringHelper *ItemName);
    void itemShowStr(char *ItemName);
    byte itemGet() { return itemCurrent; }
    byte itemNum() { return itemCount;   }

    void showMenu();            // Display menu on screen

    void moveUp();
    void moveDown();
};


class gaugeObject {
private:
    byte
        actionEnabled = 0,      // Action handler enabled. 0: False, 1: True
        dbPos,                  // database storage location for saving data
        previousState,          // Application previous state
        previousValue,          // Gauge previous value
        *gaugevalue,            // Gauge current value
        min,                    // Value min
        max,                    // Value max
        step;                   // Steps between two values
    byte
        digits(byte Number);    // Count number of digits in a number
    void
        (*actionHandler)(byte Action),      // Custom action handler on gauge, if any
        _show(byte r, byte g, byte b, uint16_t rgb, byte value);

public:
    gaugeObject() {}
    ~gaugeObject() {}


    void init(byte *variable, byte dbPosition, byte valueMin, byte valueMax, byte valueStep, const __FlashStringHelper *measureUnit, const __FlashStringHelper *Title);
    void action(byte Action);   // Receive current action from [stateAction() main.cpp loop]
    void handler(void (*functionHandler)(byte Action)); // Custom action handler to execute when gauge is set
    void Show();                // Display current value
    byte Value() { return *gaugevalue; }
};

#endif
