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

#ifndef Yacitros_font_op
#define Yacitros_font_op

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

#include "../vdu/types.h"
#include "types.h"

#include "../../yacitros/common.h"

  Yacitros_USERESULT
  _kernel_oserror *font_find(font_handle *, const char *,
                             const font_dim *, font_res *);
  Yacitros_USERESULT
  _kernel_oserror *font_readdefn(font_handle, char *, font_dim *,
                                 int *age, int *used);
  Yacitros_USERESULT
  _kernel_oserror *font_bbox(font_handle, vdu_box *);
  Yacitros_USERESULT
  _kernel_oserror *font_c_stringbbox(const char *, vdu_box *);
  Yacitros_USERESULT
  _kernel_oserror *font_set(font_handle);
  Yacitros_USERESULT
  _kernel_oserror *font_c_get(font_handle *, font_cols *);
  Yacitros_USERESULT
  _kernel_oserror *font_lose(font_handle);
  Yacitros_USERESULT
  _kernel_oserror *font_losetab(font_htab);
#define font_inittab(T) memset((T), 0, sizeof(font_htab))

  Yacitros_USERESULT
  _kernel_oserror *font_c_paint(const char *,
                                font_plottype, const vdu_point *);
  Yacitros_USERESULT
  _kernel_oserror *font_c_width(const char *,
                                const font_lim *lim, font_lim *term);

  Yacitros_USERESULT
  _kernel_oserror *font_os2mp(const vdu_point *, vdu_point *);
  Yacitros_USERESULT
  _kernel_oserror *font_mp2os(const vdu_point *, vdu_point *);

#ifdef __cplusplus
}
#endif

#endif
