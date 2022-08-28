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

#ifndef Yacitros_sprite_args
#define Yacitros_sprite_args

#ifdef __cplusplus
extern "C" {
#endif


#include "../vdu/types.h"
#include "types.h"

#include "../../yacitros/common.h"

  typedef union {
    struct {
      sprite_area area;
      const char *name;
    } byname;
    struct {
      sprite_area area;
      sprite_ptr addr;
    } byaddr;
    struct {
      uint32_t x;
      const char *name;
    } insystem;
  } sprite_spec;

  Yacitros_deprecated(typedef sprite_spec sprite_spec_t);

  typedef union {
    struct {
      sprite_area area;
      const char *name1, *name2;
    } byname;
    struct {
      sprite_area area;
      sprite_ptr addr1, addr2;
    } byaddr;
    struct {
      uint32_t x;
      const char *name1, *name2;
    } insystem;
  } sprite_spec2;

  Yacitros_deprecated(typedef sprite_spec2 sprite_spec2_t);

  typedef struct {
    const char *pathname;
    unsigned palette : 1;
  } sprite_screenioargs;

  Yacitros_deprecated(typedef sprite_screenioargs sprite_screenio_t);

  typedef struct {
    unsigned char c;
    const vdu_point *at;
    const vdu_sfact *scale;
  } sprite_charplotargs;

  Yacitros_deprecated(typedef sprite_charplotargs sprite_charplot_t);

  typedef struct {
    sprite_spec2 spec;
    unsigned vert : 1;
  } sprite_appendargs;

  Yacitros_deprecated(typedef sprite_appendargs sprite_append_t);

  typedef struct {
    sprite_spec spec;
    uint32_t number;
    int32_t amount;
  } sprite_lineargs;

  Yacitros_deprecated(typedef sprite_lineargs sprite_line_t);

  typedef struct {
    uint32_t size;
    uint32_t count;
    int32_t sprite1, free1;
  } sprite_areadimargs;

  Yacitros_deprecated(typedef sprite_areadimargs sprite_areadim_t);

  typedef struct {
    sprite_area area;
    const char *pathname;
  } sprite_areaioargs;

  Yacitros_deprecated(typedef sprite_areaioargs sprite_areaio_t);

  typedef struct {
    sprite_area area;
    char *name;
    uint32_t len;
    uint32_t ord;
  } sprite_namereqargs;

  Yacitros_deprecated(typedef sprite_namereqargs sprite_namereq_t);

  typedef struct {
    sprite_spec spec;
    const char *name;
  } sprite_copyargs;

  Yacitros_deprecated(typedef sprite_copyargs sprite_copy_t);

  typedef struct {
    sprite_spec spec;
    unsigned palette : 1;
    vdu_box *rect;
  } sprite_getargs;

  Yacitros_deprecated(typedef sprite_getargs sprite_get_t);

  typedef struct {
    sprite_spec spec;
    unsigned mask : 1, palette : 1;
    uint32_t width, height;
    int32_t mode;
  } sprite_dimsargs;

  Yacitros_deprecated(typedef sprite_dimsargs sprite_dims_t);

  typedef struct {
    sprite_spec spec;
    vdu_action action;
    const vdu_point *at;
    const vdu_colnum *pixtab;
    const vdu_sfact *scale;
  } sprite_plotargs;

  Yacitros_deprecated(typedef sprite_plotargs sprite_plot_t);

  typedef struct {
    sprite_spec spec;
    vdu_action action;
    const vdu_box *from;
    const vdu_colnum *pixtab;
    union {
      uint32_t word;
    } bit;
    union {
      const vdu_xform *matrix;
      const vdu_point (*dest)[4];
    } trans;
  } sprite_transformargs;

  Yacitros_deprecated(typedef sprite_transformargs sprite_transform_t);

  typedef struct {
    sprite_spec spec;
    uint32_t size;
    void *pal;
    int32_t mode;
  } sprite_paletteargs;

  Yacitros_deprecated(typedef sprite_paletteargs sprite_palette_t);

  typedef struct {
    sprite_spec spec;
    const vdu_point *at;
    const vdu_sfact *scale;
    const vdu_colnum *pixtab;
    union {
      uint32_t word;
      struct {
        unsigned sno : 4, setshape : 1, setpalette : 1, setsno : 1;
      } field;
    } bit;
  } sprite_pointerargs;

  Yacitros_deprecated(typedef sprite_pointerargs sprite_pointer_t);

  typedef struct {
    sprite_spec spec;
    const vdu_point *pix;
    uint32_t col, tint;
  } sprite_pixcolargs;

  Yacitros_deprecated(typedef sprite_pixcolargs sprite_pixcol_t);

  typedef struct {
    sprite_spec spec;
    const vdu_point *pix;
    unsigned mask : 1;
  } sprite_pixmaskargs;

  Yacitros_deprecated(typedef sprite_pixmaskargs sprite_pixmask_t);

  typedef struct {
    sprite_spec spec;
    void *sa;
    uint32_t op;
  } sprite_redirectargs;

  Yacitros_deprecated(typedef sprite_redirectargs sprite_redirect_t);

  typedef union {
    sprite_screenioargs screenio;
    sprite_areaioargs areaio;
    sprite_namereqargs namereq;
    sprite_copyargs copy;
    sprite_areadimargs areadim;
    sprite_getargs get;
    sprite_dimsargs dims;
    sprite_plotargs plot;
    sprite_lineargs line;
    sprite_appendargs append;
    sprite_pointerargs pointer;
    sprite_pixcolargs pixcol;
    sprite_pixmaskargs pixmask;
    sprite_charplotargs charplot;
    uint32_t size;
    sprite_area area;
    sprite_spec spec;
    sprite_ptr addr;
    sprite_transformargs transform;
    sprite_paletteargs palette;
    sprite_redirectargs redirect;
  } sprite_args;

  Yacitros_deprecated(typedef sprite_args sprite_args_t);

#ifdef __cplusplus
}
#endif

#endif
