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

#include "../riscos/time.h"

_kernel_oserror *os_readitimer(uint8_t val[5])
{
  return _swix(XOS_Word, _INR(0,1), 3, val);
}

_kernel_oserror *os_writeitimer(const uint8_t val[5])
{
  return _swix(XOS_Word, _INR(0,1), 4, val);
}

_kernel_oserror *os_readmonotonictime(os_monotime *rp)
{
  return _swix(XOS_ReadMonotonicTime, _OUT(0), rp);
}

_kernel_oserror *os_readrtclock(uint8_t val[5])
{
  val[0] = 3;
  return _swix(XOS_Word, _INR(0,1), 14, val);
}

_kernel_oserror *os_readsysclock(uint8_t val[5])
{
  return _swix(XOS_Word, _INR(0,1), 1, val);
}

_kernel_oserror *os_writesysclock(const uint8_t val[5])
{
  return _swix(XOS_Word, _INR(0,1), 2, val);
}
