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

#include <stddef.h>

#include <kernel.h>
#include <swis.h>

#include <riscos/swi/OS.h>

#include "../riscos/serial/op.h"

const float serial_rate[] = {
  9600.0, 75.0, 150.0, 300.0, 1200.0, 2400.0, 4800.0, 9600.0,
  19200.0, 50.0, 110.0, 134.5,  600.0, 1800.0, 3600.0, 7200.0
};

const unsigned serial_rateorder[] = {
  9, 1, 10, 11, 2, 3, 12, 4, 13, 5, 14, 6, 15, 0, 7, 8
};

_kernel_oserror *serial_status(unsigned *r, unsigned xor, unsigned mask)
{
  return _swix(XOS_SerialOp, r ? (_INR(0,2)|_OUT(1)) : _INR(0,2),
               0, xor, mask, r);
}

_kernel_oserror *serial_getformat(unsigned *r)
{
  return r ? _swix(XOS_SerialOp, _INR(0,1)|_OUT(1), 1, -1, r) : NULL;
}

_kernel_oserror *serial_setformat(unsigned *r, unsigned fmt)
{
  return _swix(XOS_SerialOp, r ? (_INR(0,1)|_OUT(1)) : _INR(0,1), 1, fmt, r);
}

_kernel_oserror *serial_break(unsigned cs)
{
  return _swix(XOS_SerialOp, _INR(0,1), 2, cs);
}

_kernel_oserror *serial_send(int *r, unsigned ch)
{
  _kernel_oserror *ep = _swix(XOS_SerialOp,
                              r ? (_INR(0,1)|_OUT(_FLAGS)) : _INR(0,1),
                              3, ch, r);
  if (r) *r &= _C;
  return ep;
}

_kernel_oserror *serial_gettxbaud(unsigned *b)
{
  return b ? _swix(XOS_SerialOp, _INR(0,1)|_OUT(1), 6, -1, b) : NULL;
}

_kernel_oserror *serial_settxbaud(unsigned *b, unsigned s)
{
  return _swix(XOS_SerialOp, b ? (_INR(0,1)|_OUT(1)) : _INR(0,1), 6, s, b);
}

_kernel_oserror *serial_getrxbaud(unsigned *b)
{
  return b ? _swix(XOS_SerialOp, _INR(0,1)|_OUT(1), 5, -1, b) : NULL;
}

_kernel_oserror *serial_setrxbaud(unsigned *b, unsigned s)
{
  return _swix(XOS_SerialOp, b ? (_INR(0,1)|_OUT(1)) : _INR(0,1), 5, s, b);
}

_kernel_oserror *serial_recv(int *r, unsigned ch)
{
  _kernel_oserror *ep = _swix(XOS_SerialOp,
                              r ? (_INR(0,1)|_OUT(_FLAGS)) : _INR(0,1),
                              4, ch, r);
  if (r) *r &= _C;
  return ep;
}
