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

#include "../riscos/kbd/keyname.h"

const char *const kbd_keyname[128] = {
  "Shift", "Ctrl", "Alt", "Shift (left)", "Ctrl (left)", "Alt (left)",
  "Shift (right)", "Ctrl (right)", "Alt (right)",
  "Select", "Menu", "Adjust", "", "", "", "",
  "Q", "3 #", "4 $", "5 %", "F4", "8 *", "F7", "- _", "M^", "Left",
  "K6", "K7", "F11", "F12", "F10", "Scroll Lock", "Print", "W", "E", "T",
  "7 &", "I", "9 (", "0 )", "M_", "Down", "K8", "K9", "Break/Pause", "` ~",
  "£ ¤", "Backspace", "1 !", "2 @", "D", "R", "6 ^", "U", "O", "P", "[ {",
  "Up", "K+", "K-", "Enter", "Insert", "Home", "Page Up", "Caps Lock", "A",
  "X", "F", "Y", "J", "K", "M@", "M:", "Return", "K/", "",  "K.", "Num Lock",
  "Page Down", "\" \'", "", "S", "C", "G", "H", "N", "L", "; :", "] }",
  "Delete", "K#", "K*", "", "=", "(extra)", "", "Tab", "Z", "Space Bar",
  "V", "B", "M", ", <", ". >", "/ ?", "Copy", "K0", "K1", "K3", "", "", "",
  "Escape", "F1", "F2", "F3", "F5", "F6", "F8", "F9", "\\ |", "Right", "K4",
  "K5", "K2"
};
