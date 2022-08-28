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

#include <riscos/swi/Wimp.h>

#include "../riscos/wimp/op.h"

_kernel_oserror *wimp_blockcopy(wimp_winhandle wh, const vdu_box *area,
                                const vdu_point *bl)
{
  return _swix(XWimp_BlockCopy, _INR(0,6), wh, area->min.x, area->min.y,
               area->max.x, area->max.y, bl->x, bl->y);
}

_kernel_oserror *wimp_dragbox(const wimp_dragspec *a)
{
  return _swix(XWimp_DragBox, _IN(1), a);
}

_kernel_oserror *wimp_setcolour(wimp_gcol c)
{
  return _swix(XWimp_SetColour, _IN(0), c);
}

_kernel_oserror *wimp_textcolour(wimp_gcol g)
{
  return _swix(XWimp_TextColour, _IN(0), g);
}

_kernel_oserror *wimp_setfontcolours(wimp_gcol fg, wimp_gcol bg)
{
  return _swix(XWimp_SetFontColours, _INR(1,2), fg, bg);
}

_kernel_oserror *wimp_baseofsprites(sprite_area *rom, sprite_area *ram)
{
  sprite_area tmp;
  return _swix(XWimp_BaseOfSprites, _OUTR(0,1),
               rom ? rom : &tmp,
               ram ? ram : &tmp);
}

_kernel_oserror *sprite_opswi(int sn, int op, const sprite_args *i,
                              sprite_args *o);

_kernel_oserror *wimp_spriteop(int op, const sprite_args *i, sprite_args *o)
{
  return sprite_opswi(Wimp_SpriteOp, (op & ~0x300) | 0x100, i, o);
}
