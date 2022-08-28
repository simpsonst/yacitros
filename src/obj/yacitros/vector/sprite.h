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

#ifndef Yacitros_vector_sprite
#define Yacitros_vector_sprite

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "types.h"

#include "../common.h"

  vector_spriteobj *vector_sprite_create(void);

  /* sprite object operations */
  int vector_sprite_setimage_sys(vector_spriteobj *, const char *);
  int vector_sprite_setimage_wimp(vector_spriteobj *, const char *);
  int vector_sprite_setimage_user(vector_spriteobj *,
                                  const char *, sprite_area);
  int vector_sprite_setimage_ptr(vector_spriteobj *,
                                 sprite_ptr, sprite_area);
  int vector_sprite_setinarea(vector_spriteobj *, const vector_box *);

#ifdef __cplusplus
}
#endif

#endif
