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

_kernel_oserror *wimp_opentemplate(const char *s)
{
  return _swix(XWimp_OpenTemplate, _IN(1), s);
}

_kernel_oserror *wimp_closetemplate(void)
{
  return _swix(XWimp_CloseTemplate, 0);
}

_kernel_oserror *wimp_loadtemplate(wimp_wininfo *wd, void *ws, size_t len,
                                   font_htab fh, char name[12], int *pos,
                                   size_t *used)
{
  _kernel_oserror *err;
  err = _swix(XWimp_LoadTemplate, _INR(1,6)|_OUT(2)|_OUT(6),
              (int) wd,
              (int) ws,
              (int) (len + (char *) ws),
              fh ? (int) fh : -1,
              (int) name,
              *pos,
              (int *) used,
              pos);
  *used -= (int) ws;
  return err;
}
