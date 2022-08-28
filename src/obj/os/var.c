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

#include <string.h>

#include <kernel.h>
#include <swis.h>

#include <riscos/swi/OS.h>

#include "../riscos/var.h"

_kernel_oserror *os_getvarval(const char *match, void *v, size_t *s,
                              const char **index, os_vartype *t)
{
  memset(v, 0, *s);
  return _swix(XOS_ReadVarVal, _INR(0,4)|_OUTR(2,4),
               match, v, *s, *index, *t, s, index, t);
}

_kernel_oserror *os_setvarval(const char *match, const void *v, size_t s,
                              const char **index, os_vartype *t)
{
  return _swix(XOS_SetVarVal, _INR(0,4)|_OUTR(3,4),
               match, v, s, *index, *t, index, t);
}
