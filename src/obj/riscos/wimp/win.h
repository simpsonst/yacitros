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

#ifndef Yacitros_wimp_win
#define Yacitros_wimp_win

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define wimp_WTOP        INT32_C(-1)
#define wimp_WBOTTOM     INT32_C(-2)
#define wimp_WBACKGROUND INT32_C(-1)
#define wimp_WICONBAR    INT32_C(-2)
#define wimp_WDEVICEBAR  INT32_C(-3)

#ifdef __cplusplus
}
#endif

#endif
