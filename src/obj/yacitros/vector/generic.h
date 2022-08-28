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

#ifndef Yacitros_vector_generic
#define Yacitros_vector_generic

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "types.h"

#include "../common.h"

  int vector_translate(vector_obj *, vector_ord, vector_ord);
  int vector_align(vector_obj *, const vector_box *, unsigned);

  void vector_destroy(vector_obj *p);
  int vector_getsize(vector_obj *p, size_t *sp);
  int vector_write(vector_obj *, uint8_t **, uint8_t *, vector_fonttab *);
  int vector_print(vector_obj *, FILE *, vector_fonttab *);
  int vector_getbox(vector_obj *, vector_box *, unsigned);
  int vector_getfonts(vector_obj *, vector_fonttab *);
  void vector_invalbbox(vector_obj *);
  void vector_invalsize(vector_obj *);
  void vector_invalftab(vector_obj *);

#ifdef __cplusplus
}
#endif

#endif
