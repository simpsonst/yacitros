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

#include <riscos/swi/Hourglass.h>

#include "../riscos/vdu/hourglass.h"


_kernel_oserror *vdu_hourglasson(void)
{ return _swix(XHourglass_On, 0); }

_kernel_oserror *vdu_hourglassoff(void)
{ return _swix(XHourglass_Off, 0); }

_kernel_oserror *vdu_hourglasssmash(void)
{ return _swix(XHourglass_Smash, 0); }

_kernel_oserror *vdu_hourglassstart(int cs)
{ return _swix(XHourglass_Start, _IN(0), cs); }

_kernel_oserror *vdu_hourglasspercentage(int p)
{ return _swix(XHourglass_Percentage, _IN(0), p); }

_kernel_oserror *vdu_hourglassLEDs(unsigned toggle, unsigned mask)
{ return _swix(XHourglass_LEDs, _INR(0,1), toggle, mask); }
