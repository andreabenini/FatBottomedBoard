# Hardware
Buildlog and materials provided from the hardware section
- 50x50, 2mm stainless steel sheet. Got it from a surplus sale in a local hardware store. It's a poor quality and 2nd choice
  part, thin coated with cheap black paint, poorly finished. The only thing I like of it is the stainless, 2mm is fine because
  is not too thin or thick, good enough for keys and stabs mounts. Coating has to be brushed or replaced with something else.
  Really cheap part from a surplus sale cost: 5.00 €
- [Mechanical Keyboard Plate Mounted Stabilizers](https://www.banggood.com/Mechanical-Keyboard-Plate-Mounted-Stabilizer-6_25u-Modifier-Key-Spacebar-For-104108Keys-p-1249526.html?rmmds=search&cur_warehouse=CN)
  #2 items (for backup and tests), I'll use most of them due to my extended keyboard. #2 x 8.77$

# Electronics
Schematics available in the same dir, materials required are listed below:
- #2 Teensy 2.0++ USB AVR Development Board. Builtin USB controller, 5V version, Arduino toolchain and software. Original or cloned versions are both
  fine, price range on **5~10 €** from usual far east resellers, for example [this one](
      https://www.aliexpress.com/item/4000431099525.html?spm=a2g0s.9042311.0.0.5e3c4c4djyiYr1
  ) but there're cheaper alternatives on DX, Banggood and sites like that.  
  One goes for the controller, one goes for the keyboard firmware.
- 1.8" TFT display module, 128x160 8PIN TFT LCD, ST7735S Controller Drive 8/16 Bit SPI For Arduino Micro with SD.
  Ultra cheap and quite small head up like display for various keyboard functions, connected to the ATmega32U4 for
  custom configurations, password keeper and fancy setup. Easily available across the **2~3 €** price range, just like
  [this one](
      https://www.aliexpress.com/item/32906859151.html?src=google&src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&albcp=1691306153&albag=64902423734&trgt=743612850714&crea=it32906859151&netw=u&device=c&albpg=743612850714&albpd=it32906859151&gclid=EAIaIQobChMInuu7oIiq6AIVxcmyCh1Fnw5LEAQYAiABEgJ8wPD_BwE&gclsrc=aw.ds
  )
- Spare resistors for the LCD display: 4x1K&#8486;, 1x330&#8486;
