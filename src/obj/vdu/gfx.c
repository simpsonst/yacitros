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

#include <riscos/swi/OS.h>

#include "../riscos/vdu/gfx.h"

_kernel_oserror *vdu_plot(int c, vdu_ord x, vdu_ord y)
{
  return _swix(XOS_Plot, _INR(0,2), c, x, y);
}

_kernel_oserror *vdu_setecforigin(vdu_ord x, vdu_ord y)
{
  return _swix(XOS_Plot, _INR(0,1), x, y);
}

#if false
_kernel_oserror *vdu_setwindow(vdu_ord x, vdu_ord y,
                               vdu_ord w, vdu_ord h)
{
  return charout_queue(24, x, y, x + w, y + h);
}

_kernel_oserror *vdu_setorigin(vdu_ord x, vdu_ord y)
{
  return charout_queue(29, x, y);
}

_kernel_oserror *vdu_clear(void)
{
  return charout_byte(16);
}
#endif

_kernel_oserror *vdu_readpoint(vdu_ord x, vdu_ord y, vdu_gcol *r, int *i)
{
  _kernel_oserror *ep;
  vdu_ord a, b;
  int it;
  ep = _swix(XOS_ReadPoint, _INR(0,1)|_OUTR(2,4), x, y, &a, &b, i?i:&it);
  r->byte = (a & 0x3f) | (b & 0xc0);
  return ep;
}
