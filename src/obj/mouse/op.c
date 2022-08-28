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

#include "../riscos/mouse/op.h"

_kernel_oserror *mouse_setbounds(const vdu_box *b)
{
  uint8_t block[9];
  block[0] = 1;
  block[1] = b->min.x;
  block[2] = (unsigned) b->min.x >> 8;
  block[3] = b->min.y;
  block[4] = (unsigned) b->min.y >> 8;
  block[5] = b->max.x;
  block[6] = (unsigned) b->max.x >> 8;
  block[7] = b->max.y;
  block[8] = (unsigned) b->max.y >> 8;
  return _swix(XOS_Word, _INR(0,1), 21, block);
}

_kernel_oserror *mouse_setscale(int xscale, int yscale)
{
  uint8_t block[3];

  block[0] = 2;
  block[1] = xscale;
  block[2] = yscale;
  return _swix(XOS_Word, _INR(0,1), 21, block);
}

_kernel_oserror *mouse_setpos(const vdu_point *p)
{
  uint8_t block[5];

  block[0] = 3;
  block[1] = p->x;
  block[2] = (unsigned) p->x >> 8;
  block[3] = p->y;
  block[4] = (unsigned) p->y >> 8;
  return _swix(XOS_Word, _INR(0,1), 21, block);
}

_kernel_oserror *mouse_getpos(vdu_point *p)
{
  _kernel_oserror *ep;
  uint8_t block[5];

  block[0] = 4;
  ep = _swix(XOS_Word, _INR(0,1), 21, block);
  p->x = block[1] | (block[2] << 8);
  p->y = block[3] | (block[4] << 8);
  return ep;
}

_kernel_oserror *mouse_getevent(mouse_event *e)
{
  _kernel_oserror *ep;
  ep = _swix(XOS_Mouse, _OUTR(0,3), &e->state.pos.x, &e->state.pos.y,
             &e->state.buttons.word, &e->when);
  return ep;
}
