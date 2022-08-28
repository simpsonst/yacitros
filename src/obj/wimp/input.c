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

_kernel_oserror *wimp_getpointerinfo(wimp_mouseevent *a)
{
  return _swix(XWimp_GetPointerInfo, _IN(1), a);
}

_kernel_oserror *wimp_setcaretposition(wimp_winhandle wh, wimp_iconhandle ih,
                                       const wimp_caretpos *a)
{
  return _swix(XWimp_SetCaretPosition, _INR(0,5),
               wh, ih, a->offset.x, a->offset.y, a->flags.word, a->index);
}

_kernel_oserror *wimp_getcaretposition(wimp_winhandle *wh, wimp_iconhandle *ih,
                                       wimp_caretpos *a)
{
  wimp_caretevent evd;
  _kernel_oserror *err;
  err = _swix(XWimp_GetCaretPosition, _IN(1), &evd);
  *wh = evd.wh;
  *ih = evd.ih;
  *a = evd.pos;
  return err;
}

_kernel_oserror *wimp_processkey(wimp_keycode k)
{
  return _swix(XWimp_ProcessKey, _IN(0), k);
}
