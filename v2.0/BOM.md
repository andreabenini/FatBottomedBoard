# Hardware
Buildlog and materials provided from the hardware section
- Mechanical Keyboard Plate Mounted Stabilizers, from version 1 of this project
- Black spray paint, matte black (**RAL 9005**).  Car Wax. I already had them but you can purchase them in your local hardware
  store easily.
- PBT English Language 108 Keyscaps Keys for Cherry MX Mechanical Keyboard keycap switches, black matte (because it's cool).
  Recycled them from version 1 of this project, original cost was around 9.99. There's no difference between standard Cherry keycaps
  and low profile ones, they usually fit well.
- _(R4)_ 10Pcs Transparent ABS Keycaps Mechanical keyboard Keycaps Matte Backlit Keycaps For Cherry Switch. Standard keycaps set
  (104-108) does not cover my keyboard schema and I need something more to keep up with my 120 switches. I don't want to paint them
  externally or ruin the touch. mostly recycled from version 1 too.


# Electronics
Schematics available in the same dir, materials required are listed below:
- MxLEDBit Single Switch PCB, MX/Choc/Hot Swap Socket, Cherry MX version, Led ready, 4x25pcs, ~4.90E. (each).
  That's my biggest departure from my previous fully handmade wired project, these boards are a timesaver, handy, thin, cheap and
  provide better results. They also save you a huge amount of time while wiring. 1U Amoeba pcb boards are totally fine but this one
  is cheaper to purchase in the EU (no customs). You can get discounts and a competitive price from usual PCB manufacturers even if
  it seems to be the best bet for my money here. They can perfectly fit with all Cherry MX switches including low profile ones.  
  [Single Switch PCB](https://keycapsss.com/keyboard-parts/pcbs/173/mxledbit-single-switch-pcb-mx-choc-hot-swap-socket?number=KC10133_MX)
- Original Cherry MX low profile rgb Red Switch, 120pcs, ~50E. (various discounts might apply based on the season).  
  This is obviously where most of the budget goes, discount and various prices might apply and if you have a cheaper alternative
  open an issue or let me know as a comment.  
  Before starting the flame on MX flavors I'd like to report I'm a heavy hitter and always been a cherry black fan. I also used
  cherry brown for a while but these low profiles are amazing and I finally decided to use Reds, on low profile ones the bump on
  brown does not really makes any sense to me.  
  [Original Cherry MX low profile RED](https://www.aliexpress.com/item/1005007533369880.html?spm=a2g0o.order_list.order_list_main.15.46df1802PQbq6Z)
- SMD diode, 1N4148W, SOD123 package, 2x100pcs, ~2.50E (from timely aliexpress discounts).  
  Common 1n4148 are fine too, In my case I've decided to use the SOD123 package to minimize space, through hole diodes are good as well.  
  [1N4148 Diodes](https://www.aliexpress.com/item/1005005707644429.html?spm=a2g0o.order_list.order_list_main.10.46df1802PQbq6Z)
- GTBL SK6812 SMD MINI-E RGB LED Chip Individually Addressable Full Color DC 5V, 2x100pcs, ~7.20E. (discounted in a sale on AliExpress).
  These are optional, I have plenty of high intensity 3mm white leds and there's no need to purchase these SMDs if you are considering
  manually wiring. BTW these are thinner and they perfectly fit inside low profile cherry mx switches. They are inexpensive and
  a nicely added value if you are considering a low profile layout.  
  [SK6812 SMD RGB Leds](https://www.aliexpress.com/item/1005003056797785.html?spm=a2g0o.order_list.order_list_main.5.46df1802PQbq6Z)
- Teensy 2.0++ USB AVR Development Board. Builtin USB controller, 5V version, Arduino toolchain and software. Originals or cloned
  versions are both fine, price range from usual far east resellers. This comes free from version 1 of this project. I'm using
  teensy 2++ because they provide a lot of inputs for a huge matrix like mine (120 keys). QMK keyboard firmware with some special
  mods to support my fancy remapping and add communication features to exchange data between these two MCUs

#### To be defined
    - 1.8" TFT display module, 128x160 8PIN TFT LCD, ST7735S Controller Drive 8/16 Bit SPI For Arduino Micro with SD.
      Ultra cheap and quite small head up like display for various keyboard functions, connected to the ATmega32U4 for
      custom configurations, password keeper and fancy setup. Easily available across the **2~3 €** price range
    - 1 1K&#8486; resistor for the Darlington base
    - Spare resistors for the LCD display: 6x1K&#8486;, 1x330&#8486;, 1x100&#8486;
    - Heat shrink tubing, you'd better insulate cables when you use your soldering iron


# Software
Everything is open source from this repository, no external deps required. You can pickup ready made _.hex_ binary files or compile them
on your own. Use GitHub pull requests, issues and comments here or on chat for your getting in touch.


&nbsp;
### NOTE
---
BOM defined contains all materials used for the making, prices are indicative and many components were not planned from scratch,
project is mainly based on what I've around.  

