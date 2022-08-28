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

_kernel_oserror *wimp_poll(wimp_eventmask em,
                           void *data, wimp_eventtype *rc)
{
  _kernel_oserror *err;
  err = _swix(XWimp_Poll, _INR(0,1)|_OUT(0), em, data, rc);
  return err;
}

_kernel_oserror *wimp_pollidle(wimp_eventmask em,
                               void *data, wimp_eventtype *rc,
                               os_monotime earliest)
{
  _kernel_oserror *err;
  err = _swix(XWimp_PollIdle, _INR(0,2)|_OUT(0), em, data, earliest, rc);
  return err;
}

_kernel_oserror *wimp_sendmessage_totask(wimp_eventtype e, void *d,
                                         wimp_taskhandle th)
{
  return _swix(XWimp_SendMessage, _INR(0,2), e, d, th);
}

_kernel_oserror *wimp_sendmessage_towindow(wimp_eventtype e, void *d,
                                           wimp_winhandle wh,
                                           wimp_iconhandle ih,
                                           wimp_taskhandle *thp)
{
  wimp_taskhandle tmp;
  return _swix(XWimp_SendMessage, _INR(0,3)|_OUT(2),
               e, d, wh, ih, thp ? thp : &tmp);
}

_kernel_oserror *wimp_sendmessage_broadcast(wimp_eventtype e, void *d)
{
  return _swix(XWimp_SendMessage, _INR(0,2), e, d, 0);
}

_kernel_oserror *wimp_transferblock(wimp_taskhandle srct, void *srcb,
                                    wimp_taskhandle dest, void *desb, size_t s)
{
  return _swix(XWimp_TransferBlock, _INR(0,4), srct, srcb, dest, desb, s);
}

_kernel_oserror *wimp_addmessages(const wimp_msgtype *arr)
{
  return _swix(XWimp_AddMessages, _IN(0), arr);
}

_kernel_oserror *wimp_removemessages(const wimp_msgtype *arr)
{
  return _swix(XWimp_RemoveMessages, _IN(0), arr);
}
