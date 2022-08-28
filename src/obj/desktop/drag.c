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

#include <stdio.h>

#include <kernel.h>
#include <swis.h>

#include <riscos/swi/OS.h>

#include "../riscos/time.h"
#include "../riscos/wimp/op.h"
#include "../riscos/wimp/event.h"
#include "../riscos/vdu/var.h"
#include "../riscos/vdu/modevars.h"

#include "../yacitros/desktop/drag.h"
#include "../yacitros/desktop/event.h"

#include "../yacitros/common.h"

#include "throw.h"

drag_proc *drag_method;
void *drag_handle;
event_ref drag_reg = NULL;

void drag_cancel(void)
{
  IGNORE(wimp_dragbox(NULL));
}

static event_rspcode drag_trap(void *handle, wimp_eventtype et, void *data)
{
  if (et == wimp_User_Drag_Box) {
    (*drag_method)(drag_handle, (const vdu_box *) data);
    return event_CLAIM;
  }
  return event_SHIRK;
}

static void drag_init(void)
{
  if (!drag_reg) {
    drag_reg = event_setpre(&drag_trap, NULL);
    event_select(1<<wimp_User_Drag_Box);
  }
}

Yacitros_USERESULT
int drag_window(wimp_dragtype t, drag_proc *f, void *h, wimp_winhandle w);
Yacitros_USERESULT
int drag_dashes(wimp_dragtype t, drag_proc *f, void *h,
                const vdu_box *start, const vdu_box *limit);

int drag_window(wimp_dragtype t, drag_proc *f, void *h, wimp_winhandle w)
{
  wimp_dragspec spec;
  wimp_winstateblock block;

  block.wh = w;
  THROW(wimp_getwindowstate(&block));
  spec.startpos = block.state.loc.dim.visible;
  spec.wh = w;
  spec.type = t;
  drag_method = f;
  drag_handle = h;
  drag_init();
  THROW(wimp_dragbox(&spec));
  return 0;
}

int drag_dashes(wimp_dragtype t, drag_proc *f, void *h,
                const vdu_box *start, const vdu_box *limit)
{
  wimp_dragspec spec;
  spec.startpos = *start;
  spec.parentbox = *limit;
  spec.type = t;
  drag_init();
  drag_method = f;
  drag_handle = h;
  THROW(wimp_dragbox(&spec));
  return 0;
}

int drag_iconpos(drag_proc *f, void *d,
                 wimp_winhandle wh, wimp_iconhandle ih)
{
  wimp_iconstateblock iconblock;
  wimp_winstateblock winblock;
  vdu_box limit;
  vdu_varval xlim, ylim;
  vdu_varval xeig, yeig;

  winblock.wh = wh;
  THROW(wimp_getwindowstate(&winblock));
  THROW(vdu_readmodevariable(NULL, vdu_CURRENTMODE, vdu_XWindLimit, &xlim));
  THROW(vdu_readmodevariable(NULL, vdu_CURRENTMODE, vdu_YWindLimit, &ylim));
  THROW(vdu_readmodevariable(NULL, vdu_CURRENTMODE, vdu_XEigFactor, &xeig));
  THROW(vdu_readmodevariable(NULL, vdu_CURRENTMODE, vdu_YEigFactor, &yeig));

  limit.min.x = limit.min.y = 0;
  limit.max.x = (xlim + 1) << xeig;
  limit.max.y = (ylim + 1) << yeig;

  iconblock.wh = wh;
  iconblock.ih = ih;
  THROW(wimp_geticonstate(&iconblock));
  wimp_work2screen(&winblock.state.loc.dim, &iconblock.i.bounds.min,
                   &iconblock.i.bounds.min);
  wimp_work2screen(&winblock.state.loc.dim, &iconblock.i.bounds.max,
                   &iconblock.i.bounds.max);
  return drag_dashes(wimp_drag_USER_FIXED, f, d, &iconblock.i.bounds, &limit);
}
