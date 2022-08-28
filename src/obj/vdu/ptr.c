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

#include "../riscos/vdu/ptr.h"

_kernel_oserror *vdu_setptr(const vdu_point *p)
{
  uint8_t block[5];

  block[0] = 5;
  block[1] = p->x;
  block[2] = (unsigned) p->x >> 8;
  block[3] = p->y;
  block[4] = (unsigned) p->y >> 8;
  return _swix(XOS_Word, _INR(0,1), 21, block);
}

_kernel_oserror *vdu_getptr(vdu_point *p)
{
  _kernel_oserror *ep;
  uint8_t block[5];

  block[0] = 6;
  ep = _swix(XOS_Word, _IN(0), block);
  p->x = block[1] | (block[2] << 8);
  p->y = block[3] | (block[4] << 8);
  return ep;
}

_kernel_oserror *vdu_selectptr(int *on, int *ok, int n, int k)
{
  _kernel_oserror *ep;
  _kernel_swi_regs T;
  ep = _swix(XOS_Byte, _INR(0,1)|_OUT(1), 106,
             (n & 0x7f) | (!!k << 7), &T, &T.r[1]);
  if (on) *on = T.r[1] & 0x7f;
  if (ok) *ok = !!(T.r[1] & 0x80);
  return ep;
}

