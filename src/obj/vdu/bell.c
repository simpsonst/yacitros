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

#include "../riscos/vdu/bell.h"

_kernel_oserror *vdu_getbellchannel(int *r)
{
  return r ? _swix(XOS_Byte, _INR(0,2)|_OUT(1), 211, 0, 255, r) : 0;
}

_kernel_oserror *vdu_getbellvolume(int *r)
{
  return r ? _swix(XOS_Byte, _INR(0,2)|_OUT(1), 212, 0, 255, r) : 0;
}

_kernel_oserror *vdu_getbellpitch(int *r)
{
  return r ? _swix(XOS_Byte, _INR(0,2)|_OUT(1), 213, 0, 255, r) : 0;
}

_kernel_oserror *vdu_getbellduration(int *r)
{
  return r ? _swix(XOS_Byte, _INR(0,2)|_OUT(1), 214, 0, 255, r) : 0;
}

_kernel_oserror *vdu_setbellchannel(int *r, int v)
{
  return _swix(XOS_Byte, _INR(0,2)|(r ? _OUT(1) : 0), 211, v, 0, r);
}

_kernel_oserror *vdu_setbellvolume(int *r, int v)
{
  return _swix(XOS_Byte, _INR(0,2)|(r ? _OUT(1) : 0), 212, v, 0, r);
}

_kernel_oserror *vdu_setbellpitch(int *r, int v)
{
  return _swix(XOS_Byte, _INR(0,2)|(r ? _OUT(1) : 0), 213, v, 0, r);
}

_kernel_oserror *vdu_setbellduration(int *r, int v)
{
  return _swix(XOS_Byte, _INR(0,2)|(r ? _OUT(1) : 0), 214, v, 0, r);
}
