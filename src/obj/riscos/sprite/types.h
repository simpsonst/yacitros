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

#ifndef Yacitros_sprite_types
#define Yacitros_sprite_types

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "../types.h"

#include "../../yacitros/common.h"

  typedef struct {
    uint32_t length;
    uint32_t count;
    int32_t first_sprite;
    int32_t first_free;
  } sprite_areahdr, *sprite_area;

  Yacitros_deprecated(typedef sprite_areahdr sprite_areahdr_t);
  Yacitros_deprecated(typedef sprite_area sprite_area_t);

#define sprite_SYSTEMAREA ((sprite_area) 0)
#define sprite_WIMPAREA   ((sprite_area) 1)

  typedef struct {
    int32_t next;
    char name[12];
    uint32_t width;
    uint32_t height;
    uint32_t lbit;
    uint32_t rbit;
    int32_t image;
    int32_t mask;
    int32_t mode;
  } sprite_hdr, *sprite_ptr;

  Yacitros_deprecated(typedef sprite_hdr sprite_hdr_t);
  Yacitros_deprecated(typedef sprite_ptr sprite_ptr_t);

#ifdef __cplusplus
}
#endif

#endif
