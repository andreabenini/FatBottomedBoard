# Hardware
Buildlog and materials provided from the hardware section
- 50x50cm, 2mm stainless steel sheet. Got it from a surplus sale in a local hardware store. It's a poor quality and 2nd choice
  material, thin coated with cheap black paint, poorly finished. The only thing I like of it is the stainless, 2mm is fine because
  is not too thin or thick, good enough for keys and stabs mounts. Coating has to be brushed or replaced with something else.
  Really cheap part from a surplus sale cost: 5.00 €
- DIY Oogoo. Used as a filler for the Keyboard sides. 35% Corn Starch (Maizena), 60% Transparent Silicone, 4% Neoprene glue, 1% Laser printer black toner (from an used cartridge). Basic recipe from
  [Instructables](https://www.instructables.com/id/How-To-Make-Your-Own-Sugru-Substitute/) but hardened with the Neoprene glue. Mix and apply it quickly before it dries.
- [Mechanical Keyboard Plate Mounted Stabilizers](https://www.banggood.com/Mechanical-Keyboard-Plate-Mounted-Stabilizer-6_25u-Modifier-Key-Spacebar-For-104108Keys-p-1249526.html?rmmds=search&cur_warehouse=CN)
  #2 items (for backup and tests), I'll use most of them due to my extended keyboard. #2 x 8.77$
- Black spray paint, matte black (**RAL 9005**).  Car Wax. I already had them but you can purchase these in your local hardware store easily.
- 119 Cherry Black switches. Got them for free after dismantling two acient AT/XT keyboards. These are vintage Cherry Black buttons from the 80s. Donor keyboards were reporting 1988 as the production date
  so these are original Black keys from the 1984-88 period.
- PBT English Language 108 Keyscaps Keys for Cherry MX Mechanical Keyboard Key Cap Switches, black matte (because it's cool). These are fairly good keycaps even if the price is bottom low.
  Nothing fancy but price is good and quality seems fine, time will tell how long they'll last. Just got them from Ali for only 9.99
  https://www.aliexpress.com/item/32902062981.html?spm=a2g0s.9042311.0.0.2c404c4dDWLgtp but there're even cheaper ones, just pick up your favorite color or theme, I'm my case I need black keycaps with
  backlight capabilities.
- _(R4)_ 10Pcs Transparent ABS Keycaps Mechanical keyboard Keycaps Matte Backlit Keycaps For Cherry Switch. Standard keycaps set (104-108) does not cover my keyboard schema and I need something more to
  keep up with my 119 switches. I don't want to paint them externally or ruin the touch so I bought them for some tests, pretty cheap too (**~2$**) so I can make a lot of tries. I results are nice I can
  even buy R1..R4 keys to match current switches.  
  I've found these https://www.aliexpress.com/item/4000645380162.html?spm=a2g0s.9042311.0.0.1dc24c4dvSdjEP but other alternatives are accepted as well.


# Electronics
Schematics available in the same dir, materials required are listed below:
- #2 Teensy 2.0++ USB AVR Development Board. Builtin USB controller, 5V version, Arduino toolchain and software. Original or cloned versions are both
  fine, price range on **5~10 €** from usual far east resellers, for example [this one](
      https://www.aliexpress.com/item/4000431099525.html?spm=a2g0s.9042311.0.0.5e3c4c4djyiYr1
  ) but there're cheaper alternatives on DX, Banggood and sites like that.  
  One for the controller, one for the keyboard firmware.
- 1.8" TFT display module, 128x160 8PIN TFT LCD, ST7735S Controller Drive 8/16 Bit SPI For Arduino Micro with SD.
  Ultra cheap and quite small head up like display for various keyboard functions, connected to the ATmega32U4 for
  custom configurations, password keeper and fancy setup. Easily available across the **2~3 €** price range, just like
  [this one](
      https://www.aliexpress.com/item/32906859151.html?src=google&src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&albcp=1691306153&albag=64902423734&trgt=743612850714&crea=it32906859151&netw=u&device=c&albpg=743612850714&albpd=it32906859151&gclid=EAIaIQobChMInuu7oIiq6AIVxcmyCh1Fnw5LEAQYAiABEgJ8wPD_BwE&gclsrc=aw.ds
  )
- 119 1N4148 Diodes for the keys
- TIP112 NPN Darlington Transistor. 60V 2A. Because I already had it around but you can use whatever Darlington you've around, it's better if it can handle more than 2A even if I won't use nominal 20mA on
  LEDs, they're really bright with just 10mA so this Darlington is fine as well.
- 1 1K&#8486 resistor for the Darlington base
- 117 470&#8486 resistors (for the diodes)
- 2 330&#8486 resistors (numlock and capslock), these are controlled directly from the Teensy++ not from the Darlington
- Spare resistors for the LCD display: 6x1K&#8486;, 1x330&#8486;, 1x100&#8486;


# Software
Everything is open source from this repository, no external deps.  
You can pickup ready made _.hex_ binary files or compile them on your own. GitHub pull requests, issues and comments here or on chat for your getting in touch.


&nbsp;
### NOTE
---
BOM defined contains all materials used for the making, prices are indicative and many components are not planned from scratch, project is mainly based on what I've around.  
I can keep it cheap because it's based on already purchased materials. Project started because I've scavenged vintage cherry black switches from old devices. 
Personal time and manual skills can keep the price low but this might cost you as well _(can you measure it ?)_
