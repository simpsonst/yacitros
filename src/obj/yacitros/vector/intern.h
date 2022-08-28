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

#ifndef Yacitros_vector_intern
#define Yacitros_vector_intern

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "types.h"

#include "../common.h"

  void vector_inithdr(vector_hdr *, vector_otype);
  void vector_v2dbox(draw_box *, const vector_box *);

  void vector_destroyfile(vector_fileobj *);
  int vector_getsizefile(vector_fileobj *, size_t *);
  int vector_writefile(vector_fileobj *,
                       uint8_t **, uint8_t *, vector_fonttab *);
  int vector_printfile(vector_fileobj *, FILE *, vector_fonttab *);
  int vector_getboxfile(vector_fileobj *, vector_box *, unsigned);

  void vector_destroytagged(vector_taggedobj *);
  int vector_getsizetagged(vector_taggedobj *, size_t *);
  int vector_writetagged(vector_taggedobj *,
                         uint8_t **, uint8_t *, vector_fonttab *);
  int vector_printtagged(vector_taggedobj *, FILE *, vector_fonttab *);
  int vector_getboxtagged(vector_taggedobj *, vector_box *, unsigned);
  int vector_getfontstagged(vector_taggedobj *, vector_fonttab *);

  void vector_destroygroup(vector_groupobj *);
  int vector_getsizegroup(vector_groupobj *, size_t *);
  int vector_writegroup(vector_groupobj *,
                        uint8_t **, uint8_t *, vector_fonttab *);
  int vector_printgroup(vector_groupobj *, FILE *, vector_fonttab *);
  int vector_getboxgroup(vector_groupobj *, vector_box *, unsigned);
  int vector_getfontsgroup(vector_groupobj *, vector_fonttab *);

  void vector_destroysprite(vector_spriteobj *);
  int vector_getsizesprite(vector_spriteobj *, size_t *);
  int vector_writesprite(vector_spriteobj *,
                         uint8_t **, uint8_t *, vector_fonttab *);
  int vector_printsprite(vector_spriteobj *, FILE *, vector_fonttab *);
  int vector_getboxsprite(vector_spriteobj *, vector_box *, unsigned);

  void vector_destroytext(vector_textobj *);
  int vector_getsizetext(vector_textobj *, size_t *);
  int vector_writetext(vector_textobj *,
                       uint8_t **, uint8_t *, vector_fonttab *);
  int vector_printtext(vector_textobj *, FILE *, vector_fonttab *);
  int vector_getboxtext(vector_textobj *, vector_box *, unsigned);
  int vector_getfontstext(vector_textobj *, vector_fonttab *);

  void vector_destroypath(vector_pathobj *);
  int vector_getsizepath(vector_pathobj *, size_t *);
  int vector_writepath(vector_pathobj *,
                       uint8_t **, uint8_t *, vector_fonttab *);
  int vector_printpath(vector_pathobj *, FILE *, vector_fonttab *);
  int vector_getboxpath(vector_pathobj *, vector_box *, unsigned);

  int vector_translatefile(vector_fileobj *, vector_ord, vector_ord);
  int vector_translatesprite(vector_spriteobj *, vector_ord, vector_ord);
  int vector_translatetext(vector_textobj *, vector_ord, vector_ord);
  int vector_translatetagged(vector_taggedobj *, vector_ord, vector_ord);
  int vector_translategroup(vector_groupobj *, vector_ord, vector_ord);
  int vector_translatepath(vector_pathobj *, vector_ord, vector_ord);

#ifdef __cplusplus
}
#endif

#endif
