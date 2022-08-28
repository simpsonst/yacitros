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

#ifndef Yacitros_vector_types
#define Yacitros_vector_types

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include <ddslib/dllist.h>

#include "../../riscos/drawfile/types.h"
#include "../../riscos/sprite/types.h"

#include "../common.h"

  typedef double vector_ord;
  Yacitros_deprecated(typedef vector_ord vector_ord_t);

#define vector_UNIT (1.0)
#define vector_RADIAN (1.0)
#define vector_DEGREE (3.1415926536 / 180.0)
#define vector_POINT (640.0)
#define vector_MILLIPOINT (640.0 / 1000.0)
#define vector_INCH (180.0 * 256.0)
#define vector_XFORM (256.0 * 256.0)
#define vector_MM (draw_INCH / 51.0 * 2.0)
#define vector_MITREQ (256.0 * 256.0)
#define vector_TRISCALE (256.0)

#define vector_makeord(X,U) ((vector_ord) (X) * (U))

  typedef struct {
    vector_ord x, y;
  } vector_point;
  Yacitros_deprecated(typedef vector_point vector_point_t);

  typedef struct {
    vector_point min, max;
  } vector_box;
  Yacitros_deprecated(typedef vector_box vector_box_t);

  typedef enum {
    vector_OTEXT,
    vector_OSPRITE,
    vector_OGROUP,
    vector_OTAGGED,
    vector_OPATH,
    vector_OFILE
  } vector_otype;
  Yacitros_deprecated(typedef vector_otype vector_otype_t);

  typedef struct vector_textobj vector_textobj;
  Yacitros_deprecated(typedef vector_textobj vector_textobj_t);
  typedef struct vector_spriteobj vector_spriteobj;
  Yacitros_deprecated(typedef vector_spriteobj vector_spriteobj_t);
  typedef struct vector_groupobj vector_groupobj;
  Yacitros_deprecated(typedef vector_groupobj vector_groupobj_t);
  typedef struct vector_taggedobj vector_taggedobj;
  Yacitros_deprecated(typedef vector_taggedobj vector_taggedobj_t);
  typedef struct vector_pathobj vector_pathobj;
  Yacitros_deprecated(typedef vector_pathobj vector_pathobj_t);
  typedef union vector_obj vector_obj;
  Yacitros_deprecated(typedef vector_obj vector_obj_t);
  typedef struct vector_hdr vector_hdr;
  Yacitros_deprecated(typedef vector_hdr vector_hdr_t);
  typedef struct vector_fileobj vector_fileobj;
  Yacitros_deprecated(typedef vector_fileobj vector_fileobj_t);
  typedef struct vector_fontnode *vector_fonttab;
  Yacitros_deprecated(typedef vector_fonttab vector_fonttab_t);
  typedef struct vector_subpath vector_subpath;
  Yacitros_deprecated(typedef vector_subpath vector_subpath_t);
  typedef struct vector_pathcomp vector_pathcomp;
  Yacitros_deprecated(typedef vector_pathcomp vector_pathcomp_t);

  struct vector_hdr {
    vector_otype type;
    vector_obj *parent;
    dllist_elem(vector_obj) others;
    vector_box bbox;
    size_t size;
    unsigned bboxval : 1, sizeval : 1, ftabval : 1;
  };

  typedef dllist_hdr(vector_obj) vector_list;
  Yacitros_deprecated(typedef vector_list vector_list_t);

  struct vector_fileobj {
    vector_hdr hdr;
    vector_list list;
    vector_fonttab ftab;
  };

  struct vector_groupobj {
    vector_hdr hdr;
    vector_list list;
    char name[12];
  };

  struct vector_textobj {
    vector_hdr hdr;
    char *font, *text;
    vector_ord width, height;
    vdu_palentry fore, back;
    vector_point pos;
  };

  struct vector_taggedobj {
    vector_hdr hdr;
    unsigned tag;
    vector_obj *content;
  };

  struct vector_spriteobj {
    vector_hdr hdr;
    sprite_ptr ptr;
  };

  struct vector_pathobj {
    vector_hdr hdr;
    dllist_hdr(vector_subpath) sps;
    vdu_palentry fill, line;
    draw_pathstyle style;
    vector_ord thickness;
    void *cache;
    size_t size;
  };

  struct vector_subpath {
    dllist_elem(vector_subpath) others;
    dllist_hdr(vector_pathcomp) comps;
  };

  struct vector_pathcomp {
    dllist_elem(vector_pathcomp) others;
    unsigned bezier : 1, close : 1;
    vector_point pos[3];
  };

  union vector_obj {
    vector_hdr hdr;
    vector_textobj text;
    vector_spriteobj sprite;
    vector_groupobj group;
    vector_taggedobj tagged;
    vector_pathobj path;
  };

  enum {
    vector_LEFT = 1, vector_CENTRE = 3, vector_RIGHT = 2,
    vector_BOTTOM = 4, vector_MIDDLE = 12, vector_TOP = 8
  };

  enum {
    vector_CBUTT = 0, vector_CROUND, vector_CSQUARE, vector_CTRIANGULAR
  };

  enum {
    vector_JMITRED = 0, vector_JROUND = 1, vector_JBEVELLED = 2
  };

  struct vector_fontnode {
    char *name;
    unsigned id;
    vector_fonttab left, right;
  };

#ifdef __cplusplus
}
#endif

#endif
