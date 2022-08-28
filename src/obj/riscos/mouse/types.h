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

#ifndef Yacitros_mouse_types
#define Yacitros_mouse_types

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "../vdu/types.h"
#include "../types.h"

#include "../../yacitros/common.h"

  typedef union {
    uint32_t word;
    struct {
      unsigned adjust0 : 1, menu0 : 1, select0 : 1, padding0 : 1, adjust1 : 1,
        menu1 : 1, select1 : 1, padding1 : 1, adjust2 : 1, menu2 : 1,
        select2 : 1, padding2 : 1;
    } bits;
  } mouse_buttons;
  Yacitros_deprecated(typedef mouse_buttons mouse_buttons_t);

  typedef struct {
    vdu_point pos;
    mouse_buttons buttons;
  } mouse_state;
  Yacitros_deprecated(typedef mouse_state mouse_state_t);

  typedef struct {
    mouse_state state;
    os_monotime when;
  } mouse_event;
  Yacitros_deprecated(typedef mouse_event mouse_event_t);

#ifdef __cplusplus
}
#endif

#endif
