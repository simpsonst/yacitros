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

_kernel_oserror *wimp_initialise(double version, const char *taskname,
                                 wimp_taskhandle *taskhandle,
                                 const wimp_msgtype *m)
{
  return _swix(XWimp_Initialise, _INR(0,3)|_OUT(1),
               (int) (version * 100.0), 0x4b534154, taskname, m, taskhandle);
}

_kernel_oserror *wimp_closedown(wimp_taskhandle th)
{
  return _swix(XWimp_CloseDown, _INR(0,1), th, 0x4b534154);
}

_kernel_oserror *wimp_starttask(const char *s)
{
  return _swix(XWimp_StartTask, _IN(0), s);
}

_kernel_oserror *wimp_readsysinfo(long *vp)
{
  return _swix(XWimp_ReadSysInfo, _IN(0)|_OUT(0), *vp, vp);
}
