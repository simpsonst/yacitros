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

#ifndef Yacitros_serial_op
#define Yacitros_serial_op

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

#include "../../yacitros/common.h"

  extern const float serial_rate[];
  extern const unsigned serial_rateorder[];

#define serial_MAXCODE 15

  Yacitros_USERESULT
  _kernel_oserror *serial_status(unsigned *, unsigned xor, unsigned mask);
  Yacitros_USERESULT
  _kernel_oserror *serial_getformat(unsigned *);
  Yacitros_USERESULT
  _kernel_oserror *serial_setformat(unsigned *, unsigned);
  Yacitros_USERESULT
  _kernel_oserror *serial_break(unsigned);
  Yacitros_USERESULT
  _kernel_oserror *serial_send(int *, unsigned);
  Yacitros_USERESULT
  _kernel_oserror *serial_gettxbaud(unsigned *);
  Yacitros_USERESULT
  _kernel_oserror *serial_settxbaud(unsigned *, unsigned);
  Yacitros_USERESULT
  _kernel_oserror *serial_getrxbaud(unsigned *);
  Yacitros_USERESULT
  _kernel_oserror *serial_setrxbaud(unsigned *, unsigned);
  Yacitros_USERESULT
  _kernel_oserror *serial_recv(int *, unsigned);

#ifdef __cplusplus
}
#endif

#endif
