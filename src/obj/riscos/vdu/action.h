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

#ifndef Yacitros_vdu_action
#define Yacitros_vdu_action

#ifdef __cplusplus
extern "C" {
#endif


#include <riscos/vdu/types.h>

#define vdu_OVERWRITE ((vdu_action) 0x00)
#define vdu_OR        ((vdu_action) 0x01)
#define vdu_AND       ((vdu_action) 0x02)
#define vdu_XOR       ((vdu_action) 0x03)
#define vdu_INVERT    ((vdu_action) 0x04)
#define vdu_NOP       ((vdu_action) 0x05)
#define vdu_ANDNOT    ((vdu_action) 0x06)
#define vdu_ORNOT     ((vdu_action) 0x07)
#define vdu_USEMASK   ((vdu_action) 0x08)
#define vdu_ECF1      ((vdu_action) 0x10)
#define vdu_ECF2      ((vdu_action) 0x20)
#define vdu_ECF3      ((vdu_action) 0x30)
#define vdu_ECF4      ((vdu_action) 0x40)
#define vdu_BIGECF    ((vdu_action) 0x50)

#define vdu_FOREGROUND ((vdu_ground) 0x00)
#define vdu_BACKGROUND ((vdu_ground) 0x80)

#ifdef __cplusplus
}
#endif

#endif
