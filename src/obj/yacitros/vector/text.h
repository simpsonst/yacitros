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

#ifndef Yacitros_vector_text
#define Yacitros_vector_text

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "../../riscos/vdu/types.h"

#include "types.h"

#include "../common.h"

  vector_textobj *vector_text_create(void);

  /* text object operations */
  int vector_text_setcolour(vector_textobj *,
                            vdu_palentry f, vdu_palentry b);
  int vector_text_setfont(vector_textobj *, const char *);
  int vector_text_settext(vector_textobj *, const char *);
  int vector_text_setscale(vector_textobj *,
                           vector_ord, vector_ord);
  int vector_text_setinarea(vector_textobj *,
                            const vector_box *, unsigned);

#ifdef __cplusplus
}
#endif

#endif
