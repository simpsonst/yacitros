// -*- c-basic-offset: 2; indent-tabs-mode: nil -*-

/*
    Yacitros: Yet Another C Interface to RISC OS
    Copyright (C) 2000-3,2005,2007,2012-13  Steven Simpson

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    Author contact: <https://github.com/simpsonst>
*/

#ifndef Yacitros_kbd_ikn
#define Yacitros_kbd_ikn

/* internal key numbers */

#ifdef __cplusplus
extern "C" {
#endif


#define kbd_SHIFT                        0
#define kbd_CTRL                         1
#define kbd_ALT                          2
#define kbd_SHIFT_LEFT                   3
#define kbd_CTRL_LEFT                    4
#define kbd_ALT_LEFT                     5
#define kbd_SHIFT_RIGHT                  6
#define kbd_CTRL_RIGHT                   7
#define kbd_ALT_RIGHT                    8
#define kbd_MOUSE_LEFT                   9
#define kbd_MOUSE_MIDDLE                10
#define kbd_MOUSE_RIGHT                 11
#define kbd_Q                           16
#define kbd_3                           17
#define kbd_HASH                     kbd_3
#define kbd_4                           18
#define kbd_DOLLAR                   kbd_4
#define kbd_5                           19
#define kbd_PERCENT                  kbd_5
#define kbd_F4                          20
#define kbd_8                           21
#define kbd_ASTERISK                 kbd_8
#define kbd_F7                          22
#define kbd_MINUS                       23
#define kbd_UNDERSCORE           kbd_MINUS
#define kbd_MASTER_CIRCUMFLEX           24 /* Master compatibility */
#define kbd_ARROW_LEFT                  25
#define kbd_KEYPAD_6                    26
#define kbd_KEYPAD_7                    27
#define kbd_F11                         28
#define kbd_F12                         29
#define kbd_F10                         30
#define kbd_SCROLLLOCK                  31
#define kbd_PRINT                       32
#define kbd_F0                   kbd_PRINT
#define kbd_W                           33
#define kbd_E                           34
#define kbd_T                           35
#define kbd_7                           36
#define kbd_AMPERSAND                kbd_7
#define kbd_I                           37
#define kbd_9                           38
#define kbd_ROUND_OPEN               kbd_9
#define kbd_0                           39
#define kbd_ROUND_CLOSE              kbd_0
#define kbd_MASTER_UNDERSCORE           40 /* Master compatibility */
#define kbd_ARROW_DOWN                  41
#define kbd_KEYPAD_8                    42
#define kbd_KEYPAD_9                    43
#define kbd_BREAK                       44
#define kbd_PAUSE                kbd_BREAK
#define kbd_TILDE                       45
#define kbd_APOSTROPHE_OPEN      kbd_TILDE
#define kbd_POUND                       46
#define kbd_CURRENCY             kbd_POUND
#define kbd_BACKSPACE                   47
#define kbd_1                           48
#define kbd_PLING                    kbd_1
#define kbd_2                           49
#define kbd_AT                       kbd_2
#define kbd_D                           50
#define kbd_R                           51
#define kbd_6                           52
#define kbd_CIRCUMFLEX               kbd_6
#define kbd_U                           53
#define kbd_O                           54
#define kbd_P                           55
#define kbd_SQUARE_OPEN                 56
#define kbd_BRACE_OPEN     kbd_SQUARE_OPEN
#define kbd_ARROW_UP                    57
#define kbd_KEYPAD_PLUS                 58
#define kbd_KEYPAD_MINUS                59
#define kbd_KEYPAD_ENTER                60
#define kbd_INSERT                      61
#define kbd_HOME                        62
#define kbd_PAGE_UP                     63
#define kbd_CAPSLOCK                    64
#define kbd_A                           65
#define kbd_X                           66
#define kbd_F                           67
#define kbd_Y                           68
#define kbd_J                           69
#define kbd_K                           70
#define kbd_MASTER_AT                   71 /* Master compatibility */
#define kbd_MASTER_COLON                72 /* Master compatibility */
#define kbd_RETURN                      73
#define kbd_KEYPAD_SLASH                74
#define kbd_KEYPAD_POINT                76
#define kbd_NUMLOCK                     77
#define kbd_PAGE_DOWN                   78
#define kbd_QUOTE_DOUBLE                79
#define kbd_QUOTE_SINGLE  kbd_QUOTE_DOUBLE
#define kbd_S                           81
#define kbd_C                           82
#define kbd_G                           83
#define kbd_H                           84
#define kbd_N                           85
#define kbd_L                           86
#define kbd_SEMICOLON                   87
#define kbd_COLON            kbd_SEMICOLON
#define kbd_SQUARE_CLOSE                88
#define kbd_BRACE_CLOSE   kbd_SQUARE_CLOSE
#define kbd_DELETE                      89
#define kbd_KEYPAD_HASH                 90
#define kbd_KEYPAD_ASTERISK             91
#define kbd_EQUALS                      93
#define kbd_PLUS                kbd_EQUALS
#define kbd_EXTRA                       94
#define kbd_TAB                         96
#define kbd_Z                           97
#define kbd_SPACEBAR                    98
#define kbd_V                           99
#define kbd_B                          100
#define kbd_M                          101
#define kbd_COMMA                      102
#define kbd_LESSTHAN             kbd_COMMA
#define kbd_POINT                      103
#define kbd_GREATERTHAN          kbd_POINT
#define kbd_SLASH                      104
#define kbd_QUERY                kbd_SLASH
#define kbd_COPY                       105
#define kbd_KEYPAD_0                   106
#define kbd_KEYPAD_1                   107
#define kbd_KEYPAD_3                   108
#define kbd_ESCAPE                     112
#define kbd_F1                         113
#define kbd_F2                         114
#define kbd_F3                         115
#define kbd_F5                         116
#define kbd_F6                         117
#define kbd_F8                         118
#define kbd_F9                         119
#define kbd_BACKSLASH                  120
#define kbd_VBAR             kbd_BACKSLASH
#define kbd_ARROW_RIGHT                121
#define kbd_KEYPAD_4                   122
#define kbd_KEYPAD_5                   123
#define kbd_KEYPAD_2                   124

#define kbd(N)                     kbd_##N

#ifdef __cplusplus
}
#endif

#endif
