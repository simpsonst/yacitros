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

#ifndef Yacitros_vdu_colourtrans
#define Yacitros_vdu_colourtrans

#ifdef __cplusplus
extern "C" {
#endif


#include "types.h"

#include "../../yacitros/common.h"

  Yacitros_USERESULT
  _kernel_oserror *vdu_ctransselectnearest(vdu_gcol *, vdu_palentry);
  Yacitros_USERESULT
  _kernel_oserror *vdu_ctranssetnearest(vdu_gcol *, vdu_palentry,
                                        vdu_ground, vdu_action);
  Yacitros_USERESULT
  _kernel_oserror *vdu_ctransselectfurthest(vdu_gcol *, vdu_palentry);
  Yacitros_USERESULT
  _kernel_oserror *vdu_ctranssetfurthest(vdu_gcol *, vdu_palentry,
                                         vdu_ground, vdu_action);
#if false
  /* Don't know what this was supposed to be! */
  Yacitros_USERESULT
  _kernel_oserror *vdu_ctranssetpalette(uint_least32_t,
                                        const vdu_palentry *);
#endif

#ifdef __cplusplus
}
#endif

#endif
