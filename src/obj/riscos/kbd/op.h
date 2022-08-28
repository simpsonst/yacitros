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

#ifndef Yacitros_kbd_op
#define Yacitros_kbd_op

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

#include "types.h"

  // TODO: Return _kernel_oserror * for these?

  enum { kbd_CKEDIT = 0, kbd_CKASCII = 1, kbd_CKFUNC = 2 };
  void kbd_setcursorkeys(int);
  void kbd_setdelay(int cs);
  int kbd_getdelay(void);
  void kbd_setrate(int cs);
  int kbd_getrate(void);

  int kbd_test(kbd_ikn);
  void kbd_scan(kbd_set *);
#define kbd_testscan(S,K) (S)->b[(K)/32]&(1<<(K)%32)

  int kbd_setstate(int); /* -1 means read */
#define kbd_enable() kbd_setstate(1)
#define kbd_disable() kbd_setstate(0)

#define kbd_SCROLLLED 2
#define kbd_NUMLED 4
#define kbd_CAPSLED 16
  int kbd_alterleds(int mask, int eor);
  int kbd_reflectleds(void);

  /* these should probably be somewhere else */

#define kbd_RESET 0
#define kbd_ESCAPE 1
#define kbd_NULL 2
#define kbd_BREAK 3
#define kbd_BREAK_S 12
#define kbd_BREAK_C 48
#define kbd_BREAK_CS 192
  int kbd_alterbreak(int mask, int eor);

  enum { kbd_SOFTRESET = 0, kbd_POWERRESET = 1, kbd_HARDRESET = 2 };
  int kbd_getlastreset(void);

#ifdef __cplusplus
}
#endif

#endif
