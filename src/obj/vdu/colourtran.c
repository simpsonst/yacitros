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

#include <riscos/swi/ColourTrans.h>
#include <riscos/swi/OS.h>

#include "../riscos/vdu/colourtrans.h"

_kernel_oserror *vdu_ctransselectnearest(vdu_gcol *r, vdu_palentry pe)
{
  return r ? _swix(XColourTrans_ReturnGCOL, _IN(0)|_OUT(0), pe, r) : 0;
}

_kernel_oserror *vdu_ctranssetnearest(vdu_gcol *r, vdu_palentry pe,
                                      vdu_ground g, vdu_action a)
{
  return _swix(XColourTrans_SetGCOL, _IN(0)|_INR(3,4)|(r ? _OUT(0) : 0),
               pe, g & 0xff, a & 0xff, r);
}

_kernel_oserror *vdu_ctransselectfurthest(vdu_gcol *r, vdu_palentry pe)
{
  return r ? _swix(XColourTrans_ReturnOppGCOL,
                   _IN(0)|_OUT(0), pe, r) : 0;
}

_kernel_oserror *vdu_ctranssetfurthest(vdu_gcol *r, vdu_palentry pe,
                                       vdu_ground g, vdu_action a)
{
  return _swix(XColourTrans_SetOppGCOL, _IN(0)|_INR(3,4)|(r ? _OUT(0) : 0),
               pe, g & 0xff, a & 0xff, r);
}
