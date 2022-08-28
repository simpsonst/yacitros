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

#ifndef win_COMMON_HDR
#define win_COMMON_HDR

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include <ddslib/dllist.h>

#include "../riscos/vdu/geom.h"
#include "../riscos/vdu/gfx.h"
#include "../riscos/wimp/op.h"
#include "../riscos/wimp/msgtypes.h"
#include "../riscos/wimp/event.h"
#include "../riscos/wimp/win.h"

#include "../yacitros/desktop/win.h"
#include "../yacitros/desktop/template.h"
#include "../yacitros/desktop/event.h"
#include "../yacitros/desktop/wimpmsg.h"
#include "../yacitros/desktop/help.h"
#include "../yacitros/desktop/dataxfer.h"
#include "../yacitros/desktop/task.h"
#include "../yacitros/desktop/win.h"

#define PANEDIR_DOWNWARDS

struct win {
  wimp_winhandle wh;
  event_ref eh;
  struct {
    dllist_hdr(struct win) children;
    dllist_elem(struct win) siblings;
    win_handle parent;
  } pane;
  dataxfer_msgblock savemsg;
  wimp_msgref saveref;
  unsigned xferfail : 1;
  struct {
    void *handle;
    win_redrawproc *redraw, *update;
    win_clickproc *click;
    win_keyproc *key;
    win_openproc *open;
    win_closeproc *close;
    win_scrollproc *scroll;
    win_caretmvproc *caretin;
    win_caretmvproc *caretout;
    win_ptrmvproc *ptrin;
    win_ptrmvproc *ptrout;
    win_loadproc *load;
    win_saveproc *save;
    win_resvproc *resv;
    win_filledproc *filled;
    win_helpproc *help;
    win_paneproc *pane;
  } user;
};

typedef union {
  wimp_winhandle wh;
  wimp_openwinreq owr;
  wimp_mouseevent me;
  wimp_keypressedevent kpe;
  wimp_scrollreq sr;
  wimp_caretevent ce;
  dataxfer_msgblock xfer;
  help_msgblock help;
} win_msgs;

event_rspcode win_eventproc(void *rv, wimp_eventtype et, void *datav);

#endif
