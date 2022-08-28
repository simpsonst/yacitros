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

_kernel_oserror *wimp_createicon(const wimp_createiconblock *i,
                                 wimp_iconhandle *ih)
{
  return _swix(XWimp_CreateIcon, _IN(1)|_OUT(0), i, ih);
}

_kernel_oserror *wimp_deleteicon(wimp_winhandle wh, wimp_iconhandle ih)
{
  return _swix(XWimp_DeleteIcon, _BLOCK(1), wh, ih);
}

_kernel_oserror *wimp_seticonstate(wimp_winhandle wh, wimp_iconhandle ih,
                                   wimp_iconflags eor,
                                   wimp_iconflags clear)
{
  return _swix(XWimp_SetIconState, _BLOCK(1), wh, ih, eor, clear);
}

_kernel_oserror *wimp_geticonstate(wimp_iconstateblock *a)
{
  return _swix(XWimp_GetIconState, _IN(1), a);
}

_kernel_oserror *wimp_whichicon(wimp_winhandle wh, wimp_iconhandle *ih,
                                wimp_iconflags mask, wimp_iconflags match)
{
  return _swix(XWimp_WhichIcon, _INR(0,3), wh, ih, mask, match);
}

_kernel_oserror *wimp_setpointershape(int shape_no, uint8_t *data,
                                      int width, int height, int ax, int ay)
{
  return _swix(XWimp_SetPointerShape, _INR(0,5),
               shape_no, data, width, height, ax, ay);
}

_kernel_oserror *wimp_ploticon(const wimp_iconstate *i)
{
  return _swix(XWimp_PlotIcon, _IN(1), i);
}
