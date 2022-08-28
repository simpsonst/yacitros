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

#include <kernel.h>
#include <swis.h>

#include <riscos/swi/Draw.h>

#include "../riscos/draw/op.h"

_kernel_oserror *draw_processpath_mod(void *p,
                                      unsigned s, const draw_xform *x,
                                      draw_ord f, draw_ord t,
                                      const draw_capjoin *cj,
                                      const draw_dashpat *dp)
{
  return _swix(XDraw_ProcessPath, _INR(0,7), p, s, x, f, t, cj, dp, 0);
}

_kernel_oserror *draw_processpath_fill(const void *p, unsigned s,
                                       const draw_xform *x,
                                       draw_ord f, draw_ord t,
                                       const draw_capjoin *cj,
                                       const draw_dashpat *dp)
{
  return _swix(XDraw_ProcessPath, _INR(0,7), p, s, x, f, t, cj, dp, 1);
}

_kernel_oserror *draw_processpath_fillsxs(const void *p, unsigned s,
                                          const draw_xform *x,
                                          draw_ord f, draw_ord t,
                                          const draw_capjoin *cj,
                                          const draw_dashpat *dp)
{
  return _swix(XDraw_ProcessPath, _INR(0,7), p, s, x, f, t, cj, dp, 2);
}

_kernel_oserror *draw_processpath_sz(const void *p, unsigned s,
                                     const draw_xform *x,
                                     draw_ord f, draw_ord t,
                                     const draw_capjoin *cj,
                                     const draw_dashpat *dp, size_t *sz)
{
  if (!sz)
    return 0;
  return _swix(XDraw_ProcessPath, _INR(0,7)|_OUT(0),
               p, s, x, f, t, cj, dp, 3, sz);
}

_kernel_oserror *draw_processpath_bb(const void *p, unsigned s,
                                     const draw_xform *x,
                                     draw_ord f, draw_ord t,
                                     const draw_capjoin *cj,
                                     const draw_dashpat *dp,
                                     draw_box *b,
                                     void **op)
{
#if __GNUC__ > 1 && !__STRICT_ANSI__
#warning "26-bit API used"
#endif
  return _swix(XDraw_ProcessPath, _INR(0,7)|(op?_OUT(0):0),
               p, s, x, f, t, cj, dp, 0x80000000 | (unsigned) b, op);
}

_kernel_oserror *draw_processpath_buf(const void *p, unsigned s,
                                      const draw_xform *x,
                                      draw_ord f, draw_ord t,
                                      const draw_capjoin *cj,
                                      const draw_dashpat *dp,
                                      void *b, void **op)
{
#if __GNUC__ > 1 && !__STRICT_ANSI__
#warning "26-bit API used"
#endif
  return _swix(XDraw_ProcessPath, _INR(0,7)|(op?_OUT(0):0),
               p, s, x, f, t, cj, dp, ~0x80000000 & (unsigned) b, op);
}
