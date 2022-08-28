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

#include "../riscos/vdu/screen.h"

_kernel_oserror *vdu_gethardbank(unsigned *r)
{
  return r ? _swix(XOS_Byte, _INR(0,2)|_OUT(1), 251, 0, 255, r) : 0;
}

_kernel_oserror *vdu_getsoftbank(unsigned *r)
{
  return r ? _swix(XOS_Byte, _INR(0,2)|_RETURN(1), 250, 0, 255, r) : 0;
}

_kernel_oserror *vdu_sethardbank(unsigned *r, unsigned b)
{
  return _swix(XOS_Byte, _INR(0,1)|(r ? _OUT(1) : 0), 113, b, r);
}

_kernel_oserror *vdu_setsoftbank(unsigned *r, unsigned b)
{
  return _swix(XOS_Byte, _INR(0,1)|(r ? _OUT(1) : 0), 112, b, r);
}

_kernel_oserror *vdu_vsync(void)
{
  return _swix(XOS_Byte, _IN(0), 19);
}
