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

#ifndef Yacitros_desktop_drag
#define Yacitros_desktop_drag

#ifdef __cplusplus
extern "C" {
#endif

#include "../../riscos/wimp/types.h"

#include "types.h"

#include "../common.h"

  void drag_cancel(void);
  void drag_windowpos(drag_proc *, void *, wimp_winhandle);
  void drag_windowsize(drag_proc *, void *, wimp_winhandle);
  void drag_hscroll(drag_proc *, void *, wimp_winhandle);
  void drag_vscroll(drag_proc *, void *, wimp_winhandle);
  Yacitros_USERESULT
  int drag_iconpos(drag_proc *, void *, wimp_winhandle, wimp_iconhandle);

#ifdef __cplusplus
}
#endif

#endif
