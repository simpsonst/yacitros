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

#include "../riscos/vdu/var.h"

_kernel_oserror *vdu_readmodevariable(int *r, int mode,
                                      vdu_varno var, vdu_varval *val)
{
  _kernel_oserror *ep;
  int carry;
  if (val)
    ep = _swix(XOS_ReadModeVariable, _INR(0,1)|_OUT(2)|_OUT(_FLAGS),
               mode, var, val, &carry);
  else
    ep = _swix(XOS_ReadModeVariable, _INR(0,1)|_OUT(_FLAGS),
               mode, var, &carry);
  if (r)
    *r = (carry & _C) ? -1 : 0;
  return ep;
}

_kernel_oserror *vdu_readvariables(const vdu_varno *ib, vdu_varval *ob)
{
  return _swix(XOS_ReadVduVariables, _INR(0,1), ib, ob);
}
