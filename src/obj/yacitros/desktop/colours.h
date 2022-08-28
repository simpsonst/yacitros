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

#ifndef Yacitros_desktop_colours
#define Yacitros_desktop_colours

#ifdef __cplusplus
extern "C" {
#endif

#define colours_DT0  vdu_PALENTRY(0xf0,0xf0,0xf0)
#define colours_DT1  vdu_PALENTRY(0xd0,0xd0,0xd0)
#define colours_DT2  vdu_PALENTRY(0xb0,0xb0,0xb0)
#define colours_DT3  vdu_PALENTRY(0x90,0x90,0x90)
#define colours_DT4  vdu_PALENTRY(0x70,0x70,0x70)
#define colours_DT5  vdu_PALENTRY(0x50,0x50,0x50)
#define colours_DT6  vdu_PALENTRY(0x30,0x30,0x30)
#define colours_DT7  vdu_PALENTRY(0x00,0x00,0x00)
#define colours_DT8  vdu_PALENTRY(0x90,0x40,0x00)
#define colours_DT9  vdu_PALENTRY(0x00,0xe0,0xe0)
#define colours_DT10 vdu_PALENTRY(0x00,0xc0,0x00)
#define colours_DT11 vdu_PALENTRY(0x00,0x00,0xd0)
#define colours_DT12 vdu_PALENTRY(0xb0,0xe0,0xe0)
#define colours_DT13 vdu_PALENTRY(0x00,0x80,0xf0)
#define colours_DT14 vdu_PALENTRY(0xf0,0xb0,0x00)
#define colours_DT15 vdu_PALENTRY(0x70,0x70,0x70)

#define colours_DTM0 vdu_PALENTRY(0xf0,0xf0,0x00)
#define colours_DTM1 vdu_PALENTRY(0x90,0x00,0x00)
#define colours_DTM2 vdu_PALENTRY(0xc0,0x80,0x00)

#ifdef __cplusplus
}
#endif

#endif
