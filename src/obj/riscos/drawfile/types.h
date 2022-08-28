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

#ifndef Yacitros_drawfile_types
#define Yacitros_drawfile_types

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

#include "../draw/types.h"
#include "../sprite/types.h"
#include "../vdu/types.h"

#include "../../yacitros/common.h"

#define drawfile_MAGIC (0x77617244UL)

#if false
  typedef vdu_palentry_t drawfile_colour;
  Yacitros_deprecated(typedef drawfile_colour drawfile_colour_t);

#define drawfile_PE2COL(C)      (C)
#define drawfile_COL2PE(C)      (C)
#define drawfile_COLOUR(R,G,B)  vdu_PALENTRY((R),(G),(B))
#define drawfile_COLOURF(R,G,B) vdu_PALENTRYF((R),(G),(B))
#define drawfile_GETRED(X)      vdu_GETRED(X)
#define drawfile_GETGREEN(X)    vdu_GETGREEN(X)
#define drawfile_GETBLUE(X)     vdu_GETBLUE(X)
#endif

#define drawfile_TRANSPARENT    ((vdu_palentry) 0xffffffffu)

  typedef uint32_t drawfile_otype;
  Yacitros_deprecated(typedef drawfile_otype drawfile_otype_t);

#define drawfile_OFONTTAB     UINT32_C(0)
#define drawfile_OTEXT        UINT32_C(1)
#define drawfile_OPATH        UINT32_C(2)
#define drawfile_OSPRITE      UINT32_C(5)
#define drawfile_OGROUP       UINT32_C(6)
#define drawfile_OTAGGED      UINT32_C(7)
#define drawfile_TEXTAREA     UINT32_C(9)
#define drawfile_TEXTCOL      UINT32_C(10)

  typedef struct {
    uint32_t magic, major, minor;
    char source[12];
    draw_box bbox;
  } drawfile_hdr;
  Yacitros_deprecated(typedef drawfile_hdr drawfile_hdr_t);

  typedef struct {
    drawfile_otype type;
    size_t size;
    draw_box bbox;
  } drawfile_objhdr;
  Yacitros_deprecated(typedef drawfile_objhdr drawfile_objhdr_t);

  typedef struct {
    vdu_palentry fill, outline;
    draw_ord thickness;
    draw_pathstyle style;
  } drawfile_pathobj;
  Yacitros_deprecated(typedef drawfile_pathobj drawfile_pathobj_t);

  typedef struct {
    vdu_palentry fore, back;
    uint32_t style;
    draw_ord width, height;
    draw_point base;
  } drawfile_textobj;
  Yacitros_deprecated(typedef drawfile_textobj drawfile_textobj_t);

#ifdef __cplusplus
}
#endif

#endif
