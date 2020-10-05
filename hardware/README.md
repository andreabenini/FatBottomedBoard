Hardware designs & layouts

---
**Note**
- keyboard-frame.png and poster-*.png files are just the temp result of keyboard-frame.eps, the could safely removed from here if needed
- **posterize.sh** splits `keyboard-frame.png` in pieces (`poster-*.png`) so they can be safely printed with 1:1 scale on common A4/US_Letter sheets
- QMK keyboard firmware builder is way better than TMK counterpart, use it to define wirings and create C defines
  and `KEYMAP()` proper mappings. Later on you might adapt generated code to TMK firmware. Just take a look at
  `kb.h` and `kb.c` generated files.
  **fatbottomedboard.json** was generated from https://kbfirmware.com/, you might use it again and return
  to that site to load configuration and alter it if needed.
  **keyboard-layout.json** was generated from http://www.keyboard-layout-editor.com/, you might use it again and return
  to that site to load configuration and alter it if needed.
  **keyboard-layout.[png|svg]** were generated from http://www.keyboard-layout-editor.com/ along with the json file


**Links**
- Layout editor  
  http://www.keyboard-layout-editor.com/
- Plate & Case builder  
  http://builder.swillkb.com/
- QMK Keyboard firmware builder https://kbfirmware.com/  
- Best guide *ever*, tons of suggestions in the entire process  
  https://www.reddit.com/r/MechanicalKeyboards/comments/4l0p41/guide_detailed_guide_to_making_a_custom_keyboard
- Building a keyboard from scratch (good general intro)  
  https://www.geekabit.nl/projects/building-a-keyboard-from-scratch/
- DIY keyboard collection (or how I became a KB-geek...)  
  nice case mods https://deskthority.net/viewtopic.php?f=7&t=2534&start=
- Firmware from TMK project  
  https://github.com/andreabenini/tmk_keyboard
- How to make a keyboard - The Matrix  
  powerful intro and good electrical documentation for a custom built diy keyboard, not just a ready made kit  
  http://blog.komar.be/how-to-make-a-keyboard-the-matrix/
- Brownfox keyboard, custom made keyboard, steel frame is the only thing maded outside this project  
  https://deskthority.net/viewtopic.php?f=7&t=6050&start=
- Custom made keyboard https://imgur.com/gallery/ba3jK (http://kbfirmware.com/)
- HackADay keyboard's bible  
  https://hackaday.com/tag/keyboard/
- Well explained on each single aspetct (hardware, electronics, software)  
  https://www.facebook.com/notes/wez-furlong/building-a-keyboard/10154070897701787/
- Lots of tips and tricks from this guy  
  https://matt3o.com/
- 3D printing resources  
  https://www.reddit.com/r/MechanicalKeyboards/wiki/3dprinting
- Key modifications  
  https://www.reddit.com/r/MechanicalKeyboards/wiki/key_modifications
- DIY resources from geekhack  
  https://geekhack.org/index.php?topic=69582.0
- Minimal Animal Keyboard  
  This guy did a really good job with its creation, just take a look at **imgur** to see it.  
  I'm also considering his important notes related to backlight  
  https://deskthority.net/viewtopic.php?f=7&t=7615&start=  
  https://deskthority.net/viewtopic.php?f=7&t=7779&start=  
  https://imgur.com/a/sWuH1



**Stabilizers**
- Cherry stabilizers mounting (under the plate)  
  https://www.youtube.com/watch?v=a173Blgfmww
- How To Assemble Cherry PCB Mount Stabilizers  
  https://www.youtube.com/watch?v=u-HYNmtP1Hc
- Cherry plate mounted stabilizers [7u,6.25u,2u]. Cheapest price found, they seems to be quite decent clones, don't know about the quality  
  https://www.aliexpress.com/item/32717878890.html
