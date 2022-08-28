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

#ifndef Yacitros_wimp_button
#define Yacitros_wimp_button

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define wimp_BALWAYS          UINT32_C(0)
#define wimp_BREPEAT          UINT32_C(1)
#define wimp_BCLICK           UINT32_C(2)
#define wimp_BRELEASE         UINT32_C(3)
#define wimp_BDOUBLECLICK     UINT32_C(4)
#define wimp_BCLICKDRAG       UINT32_C(5)
#define wimp_BRELEASEDRAG     UINT32_C(6)
#define wimp_BDOUBLEDRAG      UINT32_C(7)
#define wimp_BMENUICON        UINT32_C(8)
#define wimp_BDOUBLECLICKDRAG UINT32_C(9)
#define wimp_BRADIO           UINT32_C(10)
#define wimp_BWRITECLICKDRAG  UINT32_C(14)
#define wimp_BWRITEABLE       UINT32_C(15)

#ifdef cplusplus
}
#endif

#endif
