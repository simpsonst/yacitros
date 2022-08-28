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

#ifndef Yacitros_font_types
#define Yacitros_font_types

#ifdef __cplusplus
extern "C" {
#endif


#include <string.h>
#include <stdint.h>

#include "../vdu/types.h"

#include "../../yacitros/common.h"

  typedef uint8_t font_handle;
  Yacitros_deprecated(typedef font_handle font_t);
  typedef font_handle font_htab[256];
  Yacitros_deprecated(typedef font_htab font_htab_t);

  typedef uint32_t font_dpi, font_16thpt;
  Yacitros_deprecated(typedef font_dpi font_dpi_t);
  Yacitros_deprecated(typedef font_16thpt font_16thpt_t);

  typedef struct {
    font_16thpt x, y;
  } font_size;
  Yacitros_deprecated(typedef font_size font_size_t);

  typedef struct {
    font_dpi x, y;
  } font_res;
  Yacitros_deprecated(typedef font_res font_res_t);

  typedef struct {
    font_size size;
    font_res res;
  } font_dim;
  Yacitros_deprecated(typedef font_dim font_dim_t);

  typedef struct {
    vdu_palentry bg, fg, fgo;
  } font_cols;
  Yacitros_deprecated(typedef font_cols font_cols_t);

  typedef struct {
    vdu_point pos;
    int split, len;
  } font_lim;
  Yacitros_deprecated(typedef font_lim font_lim_t);

  typedef unsigned int font_plottype;
  Yacitros_deprecated(typedef font_plottype font_plot_t);
#define font_JUSTIFY   (1u)
#define font_RUBOUT    (2u)
#define font_OSCOORDS (16u)

#ifdef __cplusplus
}
#endif

#endif
