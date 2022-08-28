// -*- c-basic-offset: 2; indent-tabs-mode: nil -*-

/*
    Yacitros: Yet Another C Interface to RISC OS
    Copyright (C) 2000,3,5.7  Steven Simpson

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

#ifndef Yacitros_mouse_op
#define Yacitros_mouse_op

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

#include "../vdu/types.h"
#include "types.h"

#include "../../yacitros/common.h"

  Yacitros_USERESULT
  _kernel_oserror *mouse_setbounds(const vdu_box *);
  Yacitros_USERESULT
  _kernel_oserror *mouse_setscale(int xscale, int yscale);
  Yacitros_USERESULT
  _kernel_oserror *mouse_setpos(const vdu_point *);
  Yacitros_USERESULT
  _kernel_oserror *mouse_getpos(vdu_point *);
  Yacitros_USERESULT
  _kernel_oserror *mouse_getevent(mouse_event *);

#ifdef __cplusplus
}
#endif

#endif
