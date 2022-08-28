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

#ifndef Yacitros_wimp_key
#define Yacitros_wimp_key

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define wimp_KESCAPE UINT32_C(0x1b)
#define wimp_KPRINT  UINT32_C(0x180)
#define wimp_KF1     UINT32_C(0x181)
#define wimp_KF2     (wimp_KF1 + 1)
#define wimp_KF3     (wimp_KF2 + 1)
#define wimp_KF4     (wimp_KF3 + 1)
#define wimp_KF5     (wimp_KF4 + 1)
#define wimp_KF6     (wimp_KF5 + 1)
#define wimp_KF7     (wimp_KF6 + 1)
#define wimp_KF8     (wimp_KF7 + 1)
#define wimp_KF9     (wimp_KF8 + 1)
#define wimp_KTAB     UINT32_C(0x18a)
#define wimp_KCOPY    UINT32_C(0x18b)
#define wimp_KLEFT    UINT32_C(0x18c)
#define wimp_KRIGHT   UINT32_C(0x18d)
#define wimp_KDOWN    UINT32_C(0x18e)
#define wimp_KUP      UINT32_C(0x18f)
#define wimp_KF10     UINT32_C(0x1ca)
#define wimp_KF11     (wimp_KF10 + 1)
#define wimp_KF12     (wimp_KF11 + 1)
#define wimp_KINSERT  UINT32_C(0x1cd)
#define wimp_KCTRL    UINT32_C(0x20)
#define wimp_KSHIFT   UINT32_C(0x10)

#ifdef __cplusplus
}
#endif

#endif
