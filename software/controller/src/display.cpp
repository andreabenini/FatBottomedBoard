#include "display.h"
extern TFT display;


/**
 * Clear Screen
 */
void displayClear() {
    display.background(0, 0, 0);
} /**/


/**
 * Display error message
 */
void displayErrorMessage(const __FlashStringHelper *errorType) {
    display.background(0, 0, 0);
    display.setTextSize(2);
    display.stroke(0, 0, 255);
    display.setCursor(0, 20);    display.print(F("S D   C A R D\n  E R R O R"));
    display.setCursor(0, 80);    display.print(errorType);
    delay(5000);
} /**/


/**
 * Display incoming remote config (please wait...)
 */
void displayRemoteConfigWaiting() {
    display.background(0, 0, 0);
    display.setTextSize(2);
    display.stroke(255, 255, 255);
    display.setCursor(0, 20); display.print(F(" R E M O T E"));
    display.setCursor(0, 45); display.print(F(" C O N F I G"));
    display.setCursor(0, 70); display.print(F(" P L E A S E"));
    display.setCursor(0, 95); display.print(F("   W A I T"));
} /**/


/**
 * INIT - Init menu object, screen and internal variables. Second stage constructor
 * @param const __FlashStringHelper *TitleName     Menu Title
 * @param byte TitleXPos        X Position for the title
 * @param byte TitleYPos        Y Position for the title
 * @param byte itemSelected     Currently selected item on the entire list, starting from 0
 * @param byte itemPageCurrent  Currently selected item (from 0 to [itemPageMax])
 * @param byte itemPageMax      Maximum number of items per page
 * @param byte XposFirst        X Position of the first element of the menu
 * @param byte YposFirst        Y Position of the first element of the menu
 * @param byte YspaceItems      Y space gap between two items
 * @param void (*menuShow)())   Function pointer containing items to display
 * 
 * @see   Example:
 *          menu.init(  F("MAIN MENU"),
 *                      30,             // XPos Title
 *                      1,              // YPos Title
 *                      0,              // Current selected item
 *                      0,              // Page selected item
 *                      7,              // Page max items
 *                      5,              // X Pos first item
 *                      20,             // Y Pos first item
 *                      16,             // Y space between items
 *                      menuShow        // Display function handler
 *          );
 */
void menuObject::init(
            const __FlashStringHelper *TitleName, byte TitleXPos, byte TitleYPos,
            byte itemSelected, byte itemPageCurrent, byte itemPageMax, byte XposFirst, byte YposFirst, byte YspaceItems,
            void (*menuShow)()) {

    // Object properties
    this->XStart = XposFirst;
    this->YStart = YposFirst;
    this->YDiff  = YspaceItems;
    this->PagePos = itemPageCurrent;
    this->PageMax = itemPageMax;
    this->itemCurrent = itemSelected;
    this->itemPrevious = 0xFF;                          // init: something not visible on screen
    this->show = menuShow;

    // Some display stuff
    display.background(0, 0, 0);
    display.fillRect(0, 0, 160, YposFirst, 0xF522);   // Clear display for the title part
    display.stroke(0, 0, 0);
    display.setTextSize(2);
    display.setCursor(TitleXPos, TitleYPos);
    display.print(TitleName);
    display.stroke(255, 255, 255);
    display.setTextSize(1.98);
    display.fillRect(0, 30, 160, 98, 0x0000);           // Clear display for the menu part
    showMenu();
} /**/

void menuObject::showMenu() {
    itemCount = 0;
    YPos = YStart;
    show();
}

/**
 * ITEM SHOW - Add item to the menu and show it as well
 */
void menuObject::itemShow(const __FlashStringHelper *ItemName) {
    // Display item on screen only if possible
    if (itemCount >= itemCurrent-PagePos && itemCount < itemCurrent+(PageMax-PagePos)) {
        // Current item is the selected one
        if (itemCount == itemCurrent) {
            display.fillRect(0, YPos-4, 160, YDiff, 0xFA04);
            display.stroke(0, 0, 0);
            display.setCursor(XStart, YPos);
            display.print(ItemName);
            display.stroke(255, 255, 255);
        } else {
            // Current item was the previously selected, clear previous box
            if (itemCount == itemPrevious || PagePos == 0 || PagePos == PageMax-1) {
                display.fillRect(0, YPos-4, 160, YDiff, 0x0000);
            }
            display.setCursor(XStart, YPos);
            display.print(ItemName);
        }
        YPos += YDiff;
    }
    itemCount++;
} /**/


/**
 * ITEM SHOW STR - Add item to the menu and show it as well
 * @see Basically it's a copy of ::itemShow(). Duplicating code is slightly inefficient if maintaining
 *      the code base it's the only issue. This method wastes only ~50b of eeprom space but it's
 *      preferred for speed and used to avoid mixing F() strings, eeprom and stack/mem space.
 */
void menuObject::itemShowStr(char *ItemName) {
    // Display item on screen only if possible
    if (itemCount >= itemCurrent-PagePos && itemCount < itemCurrent+(PageMax-PagePos)) {
        // Current item is the selected one
        if (itemCount == itemCurrent) {
            display.fillRect(0, YPos-4, 160, YDiff, 0xFA04);
            display.stroke(0, 0, 0);
            display.setCursor(XStart, YPos);
            display.print(ItemName);
            display.stroke(255, 255, 255);
        } else {
            // Current item was the previously selected, clear previous box
            if (itemCount == itemPrevious || PagePos == 0 || PagePos == PageMax-1) {
                display.fillRect(0, YPos-4, 160, YDiff, 0x0000);
            }
            display.setCursor(XStart, YPos);
            display.print(ItemName);
        }
        YPos += YDiff;
    }
    itemCount++;
} /**/


/**
 * Move to previous option
 */
void menuObject::moveUp() {
    itemPrevious = itemCurrent;
    if (itemCurrent <= 0) {                             // First element, go to last one
        itemCurrent = itemCount-1;
        if (itemCount < PageMax) {
            PagePos = PageMax - (PageMax % itemCount);
        } else {
            PagePos = PageMax - 1;
        }        
    } else {
        itemCurrent--;
        if (PagePos > 0) {
            PagePos--;
        }
    }
    showMenu();
} /**/


/**
 * Move to next option
 */
void menuObject::moveDown() {
    itemPrevious = itemCurrent;
    if (itemCurrent >= itemCount-1) {                   // Last element, go back to first
        itemCurrent = 0;
        PagePos = 0;
    } else {
        itemCurrent++;
        if (PagePos < PageMax - 1) {
            PagePos++;
        } else {
            PagePos = PageMax - 1;
        }
    }
    showMenu();
} /**/


void gaugeObject::init(byte *variable, byte dbPosition, byte valueMin, byte valueMax, byte valueStep, const __FlashStringHelper *measureUnit, const __FlashStringHelper *Title) {
    // Object properties
    min  = valueMin;
    max  = valueMax;
    step = valueStep;
    dbPos = dbPosition;
    gaugevalue = variable;
    previousValue = *gaugevalue;
    previousState = stateGet();
    // Background graphics
    display.background(0, 0, 0);                // Clear the screen, black background
    display.fillRect(0, 0, 160, 25, 0xF522);
    display.stroke(0, 0, 0);
    display.setCursor((display.width()-strlen_P((PGM_P)Title)*6)/2, 10);        // Title
    display.print(Title);
    display.stroke(255, 255, 255);              // Measure Unit
    display.setCursor((display.width()-strlen_P((PGM_P)measureUnit)*6)/2, 70);
    display.print(measureUnit);
    display.stroke(0, 255, 255);                // Min/Max
    display.setTextSize(2);
    display.setCursor(  2, 73);
    display.print(min);
    display.setCursor((display.width()-digits(max)*12-2), 73);
    display.print(max);
    display.drawRect(10, 90, 140, 30, 0x07FF);  // Gauge outer rectangle
    display.setTextSize(4);
    stateSet(STATUS_GAUGE);
} /**/


void gaugeObject::Show() {
    _show(  0,  0,  0, 0x0000, previousValue);
    _show(255,255,255, 0x07FF, *gaugevalue);
    previousValue = *gaugevalue;
} /**/


void gaugeObject::_show(byte r, byte g, byte b, uint16_t rgb, byte value) {
    display.fillRect(15, 95, 130*value/max, 20, rgb);   // Gauge rectangle [130 width]
    display.stroke(r, g, b);                            // Caption value
    display.setCursor((display.width()-digits(value)*20)/2, 35);
    display.print(value);
} /**/


// Number of digits in a number
byte gaugeObject::digits(byte Number) {
    byte count=0;
    while (Number != 0) {
        Number /= 10;
        count++;
    }
    return count;
} /**/


void gaugeObject::handler(void (*functionHandler)(byte Action)) {
    actionEnabled = 1;
    actionHandler = functionHandler;
}


// Rotary encoder control on gauge
void gaugeObject::action(byte Action) {
    switch (Action) {
    case ACTION_CONTROL_LEFT:       // Control rotary encoder movement [UP]
        *gaugevalue = *gaugevalue-step > min ? *gaugevalue-step: min;
        if (actionEnabled != 0) {
            actionHandler(GAUGE_UP);
        }
        break;
    case ACTION_CONTROL_RIGHT:      // Control rotary encoder movement [DOWN]
        *gaugevalue = *gaugevalue+step < max ? *gaugevalue+step: max;
        if (actionEnabled != 0) {
            actionHandler(GAUGE_DOWN);
        }
        break;
    case ACTION_CONTROL_BUTTON:     // Control button press
        configWrite(dbPos, *gaugevalue);
        actionEnabled = 0;
        stateSet(previousState);
        return;
    }
    Show();
} /**/
