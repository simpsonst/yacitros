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

#ifndef Yacitros_vector_path
#define Yacitros_vector_path

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "../../riscos/vdu/types.h"

#include "types.h"

#include "../common.h"

  vector_pathobj *vector_path_create(void);

  /* path object operations */
  int vector_path_setlinecolour(vector_pathobj *, vdu_palentry);
  int vector_path_setfillcolour(vector_pathobj *, vdu_palentry);
  int vector_path_setwidth(vector_pathobj *, vector_ord);
  int vector_path_setwidth(vector_pathobj *p, vector_ord w);
  int vector_path_setjoin(vector_pathobj *p, unsigned s);
  int vector_path_setstartcap(vector_pathobj *p, unsigned s);
  int vector_path_setendcap(vector_pathobj *p, unsigned s);
  int vector_path_setwind(vector_pathobj *p, unsigned s);

  int vector_path_reset(vector_pathobj *);
  int vector_path_move(vector_pathobj *, vector_ord, vector_ord);
  int vector_path_draw(vector_pathobj *, vector_ord, vector_ord);
  int vector_path_bezier(vector_pathobj *,
                         vector_ord, vector_ord,
                         vector_ord, vector_ord,
                         vector_ord, vector_ord);
  int vector_path_arc(vector_pathobj *, vector_ord,
                      vector_ord, vector_ord);
  int vector_path_close(vector_pathobj *);

#ifdef __cplusplus
}
#endif

#endif
