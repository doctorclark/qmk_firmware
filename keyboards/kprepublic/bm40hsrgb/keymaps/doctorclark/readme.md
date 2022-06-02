# Personal Layout of [doctorclark](https://github.com/doctorclark)

Purposes: discover and clarify ways to control lighting on this board.

#####Keycap sizes
All are 1u in height--widths shown below
```
,-----------------------------------------------------------------------.
| 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | *R3 keycaps*
|-----------------------------------------------------------------------+
| 1.25u | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  |  1.75u  | *R2 keycaps*
|-----------------------------------------------------------------------+
|    2u     | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | 1u  | *R1 keycaps*
|-----------------------------------------------------------------------+
| 1u  | 1u  | 1u  |      2.75u     |    2.25u   | 1u  | 1u  | 1u  | 1u  | *R1 keycaps*
`-----------------------------------------------------------------------'
```

#####RGB LED #s
The underglow LEDs "wrap backwards" right to left in the approximate locations below, relative to the top keys.
```
,-----------------------------------------------------------------------.
|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | 10  | 11  |
|-----------------------------------------------------------------------+
|  12   | 13  | 14  | 15  | 16  | 17  | 18  | 19  | 20  | 21  |   22    |
|-----------------------------------------------------------------------+
|     23    | 24  | 25  | 26  | 27  | 28  | 29  | 30  | 31  | 32  | 33  |
|-----------------------------------------------------------------------+
| 34  | 35  | 36  |       37       |     38     | 39  | 40  | 41  | 42  |
`-----------------------------------------------------------------------'
Under:     48        47       46        45       44        43
```

# Layers
(Current layout visualization at https://ddc.me/bm43doctorclark)

#####BASE layer
This is pretty much standard except for the [Grave Escape](https://docs.qmk.fm/#/feature_grave_esc) ("EGRV"), the [mod-tapped](https://docs.qmk.fm/#/mod_tap) left shift / capslock, and the two [layer](https://docs.qmk.fm/#/feature_layers) tap-toggles. 
```
,-----------------------------------------------------------------------.
|EGRV |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |Bscp |
|-----------------------------------------------------------------------+
| Tab   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Enter  |
|-----------------------------------------------------------------------+
|Shift/Caps |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  UP |  .  |
|-----------------------------------------------------------------------+
|Ctrl | Win | Alt |      TTL1     |    Space    |TTL2 | LT  |  DN | RT  |
`-----------------------------------------------------------------------'
```

#####NUMPAD layer
This layout tries to position match as close as possible the numbers and math symbol placement as a standard num-pad. However, this layout uses the keycodes from the standard "row 4" numbers, so that other punctuation symbols (e.g., "!") can be accessed. (The only drawbacks to this are the loss of ability to enter ALT codes, and the "loss" of the non-numlock features of the standard numpad keys.)
```
,-----------------------------------------------------------------------.
|TO() |RTOG |RVAD |RVAI |     |     |  -  |  7  |  8  |  9  |  0  | Del |
|-----------------------------------------------------------------------+
| Tab   |     |     |     |     |     |  ;  |  4  |  5  |  6  |    =    |
|-----------------------------------------------------------------------+
|Shift/Caps |     |     |     |     |  '  |  1  |  2  |  3  |  *  |  /  |
|-----------------------------------------------------------------------+
|Ctrl |Btn1 |Btn2 |  Space        |         0   |  .  |  +  |  -  | ENT |
`-----------------------------------------------------------------------'
```

#####PLAYER layer
This layer has: 
- Function keys (matching the numpad numbering)
- Mouse controls including 
  - Main mouse buttons on the two space bars
  - Buttons 4 and 5 (back and forward)
  - Mouse scrolling, including button 3 for applications that use that style of scrolling
- Boot mode enable
- Document navigation including page-up/down and home/end
- Volume mute and volume up/down
```
,-----------------------------------------------------------------------.
|TO() |Btn3 | WhU |     |BOOT |VOLU |VOLD | F7  | F8  | F9  | F10 |Bscp |
|-----------------------------------------------------------------------+
| Tab   | WhL | WhD | WhR |     |     |     | F4  | F5  | F6  |     \   |
|-----------------------------------------------------------------------+
|Shift/Caps |     |     |     |     |VMUTE| F1  | F2  |  [  |PGUP |  ]  |
|-----------------------------------------------------------------------+
|Ctrl |Btn4 |Btn5 |     Btn1      |     Btn2    |     |HOME |PGDN | END |
`-----------------------------------------------------------------------'
```
