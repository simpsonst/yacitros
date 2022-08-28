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

_kernel_oserror *wimp_createwindow(const wimp_wininfo *w, wimp_winhandle *wh)
{
  return _swix(XWimp_CreateWindow, _IN(1)|_OUT(0), w, wh);
}

_kernel_oserror *wimp_deletewindow(wimp_winhandle wh)
{
  return _swix(XWimp_DeleteWindow, _IN(1), &wh);
}

_kernel_oserror *wimp_openwindow(const wimp_openwinreq *block)
{
  return _swix(XWimp_OpenWindow, _IN(1), block);
}

_kernel_oserror *wimp_closewindow(wimp_winhandle wh)
{
  return _swix(XWimp_CloseWindow, _IN(1), &wh);
}

_kernel_oserror *wimp_redrawwindow(wimp_rectangleblock *block, int *more)
{
  return _swix(XWimp_RedrawWindow, _IN(1)|_OUT(0), block, more);
}

_kernel_oserror *wimp_updatewindow(wimp_rectangleblock *block, int *more)
{
  return _swix(XWimp_UpdateWindow, _IN(1)|_OUT(0), block, more);
}

_kernel_oserror *wimp_getrectangle(wimp_rectangleblock *block, int *more)
{
  return _swix(XWimp_GetRectangle, _IN(1)|_OUT(0), block, more);
}

_kernel_oserror *wimp_getwindowstate(wimp_winstateblock *block)
{
  return _swix(XWimp_GetWindowState, _IN(1), block);
}

_kernel_oserror *wimp_getwindowinfo(wimp_wininfoblock *block)
{
  return _swix(XWimp_GetWindowInfo, _IN(1), block);
}

_kernel_oserror *wimp_forceredraw(wimp_winhandle wh, const vdu_box *ap)
{
  return _swix(XWimp_ForceRedraw, _INR(0,4), wh,
               ap->min.x, ap->min.y, ap->max.x, ap->max.y);
}

_kernel_oserror *wimp_getwindowoutline(wimp_outlineblock *block)
{
  return _swix(XWimp_GetWindowOutline, _IN(1), block);
}

_kernel_oserror *wimp_setextent(wimp_winhandle wh, const vdu_box *a)
{
  return _swix(XWimp_SetExtent, _INR(0,1), wh, a);
}
