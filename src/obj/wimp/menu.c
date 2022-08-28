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

_kernel_oserror *wimp_createmenu(const wimp_menuhdr *a,
                                 vdu_ord x, vdu_ord y)
{
  return _swix(XWimp_CreateMenu, _INR(1,3), a, x, y);
}

_kernel_oserror *wimp_closemenu(void)
{
  return _swix(XWimp_CreateMenu, _IN(1), -1);
}

_kernel_oserror *wimp_createmenuwindow(wimp_winhandle a, vdu_ord x, vdu_ord y)
{
  return _swix(XWimp_CreateMenu, _INR(1,3), a, x, y);
}

_kernel_oserror *wimp_decodemenu(const wimp_menuhdr *a,
                                 const wimp_menuchoice *b, char *answer)
{
  return _swix(XWimp_DecodeMenu, _INR(1,3), a, b, answer);
}

_kernel_oserror *wimp_createsubmenu(const wimp_menuhdr *h,
                                    vdu_ord x, vdu_ord y)
{
  return _swix(XWimp_CreateSubMenu, _INR(1,3), h, x, y);
}

_kernel_oserror *wimp_createsubmenuwindow(wimp_winhandle h,
                                          vdu_ord x, vdu_ord y)
{
  return _swix(XWimp_CreateSubMenu, _INR(1,3), h, x, y);
}

_kernel_oserror *wimp_getmenustate(wimp_winhandle wh, wimp_iconhandle ih,
                                   wimp_menuchoice *res)
{
  return _swix(XWimp_GetMenuState, _INR(0,3), 1, res, wh, ih);
}
