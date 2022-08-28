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

#ifndef Yacitros_draw_op
#define Yacitros_draw_op

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include <kernel.h>

#include "../types.h"
#include "types.h"

#include "../../yacitros/common.h"

  Yacitros_USERESULT
  _kernel_oserror *draw_processpath_mod(void *, unsigned, const draw_xform *,
                                        draw_ord, draw_ord,
                                        const draw_capjoin *,
                                        const draw_dashpat *);

  Yacitros_USERESULT
  _kernel_oserror *draw_processpath_fill(const void *, unsigned,
                                         const draw_xform *,
                                         draw_ord, draw_ord,
                                         const draw_capjoin *,
                                         const draw_dashpat *);

  Yacitros_USERESULT
  _kernel_oserror *draw_processpath_fillsxs(const void *, unsigned,
                                            const draw_xform *,
                                            draw_ord, draw_ord,
                                            const draw_capjoin *,
                                            const draw_dashpat *);

  Yacitros_USERESULT
  _kernel_oserror *draw_processpath_sz(const void *, unsigned,
                                       const draw_xform *,
                                       draw_ord, draw_ord,
                                       const draw_capjoin *,
                                       const draw_dashpat *, size_t *);

  Yacitros_USERESULT
  _kernel_oserror *draw_processpath_bb(const void *, unsigned,
                                       const draw_xform *,
                                       draw_ord, draw_ord,
                                       const draw_capjoin *,
                                       const draw_dashpat *,
                                       draw_box *, void **);

  Yacitros_USERESULT
  _kernel_oserror *draw_processpath_buf(const void *, unsigned,
                                        const draw_xform *,
                                        draw_ord, draw_ord,
                                        const draw_capjoin *,
                                        const draw_dashpat *,
                                        void *, void **);

  Yacitros_USERESULT
  _kernel_oserror *draw_fill(const void *, unsigned,
                             const draw_xform *, draw_ord);
  Yacitros_USERESULT
  _kernel_oserror *draw_stroke(const void *, unsigned, const draw_xform *,
                               draw_ord, draw_ord, const draw_capjoin *,
                               const draw_dashpat *);
  Yacitros_USERESULT
  _kernel_oserror *draw_strokepath_sz(const void *, unsigned,
                                      const draw_xform *,
                                      draw_ord, draw_ord,
                                      const draw_capjoin *,
                                      const draw_dashpat *, size_t *);
  Yacitros_USERESULT
  _kernel_oserror *draw_strokepath_buf(const void *, unsigned,
                                       const draw_xform *,
                                       draw_ord, draw_ord,
                                       const draw_capjoin *,
                                       const draw_dashpat *,
                                       void *, void **);
  Yacitros_USERESULT
  _kernel_oserror *draw_flattenpath_sz(const void *, draw_ord, size_t *);
  Yacitros_USERESULT
  _kernel_oserror *draw_flattenpath_buf(const void *, draw_ord,
                                        void *, void **);
  Yacitros_USERESULT
  _kernel_oserror *draw_transformpath_mod(void *, const draw_xform *);
  Yacitros_USERESULT
  _kernel_oserror *draw_transformpath_buf(const void *, const draw_xform *,
                                          void *, void *);

#ifdef __cplusplus
}
#endif

#endif
