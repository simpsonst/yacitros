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

#include "../riscos/wimp/op.h"
#include "../riscos/wimp/msgtypes.h"
#include "../riscos/wimp/event.h"

#include "../yacitros/desktop/mode.h"
#include "../yacitros/desktop/wimpmode.h"
#include "../yacitros/desktop/event.h"
#include "../yacitros/desktop/wimpmsg.h"

#include "throw.h"

static wimpmode_state wimpmode_data;

struct wimpmode_ctxt {
  wimpmode_state *st;
  event_ref eh;
  void (*ufp)(void *);
  void *ud;
};

struct wimpmode_ctxt wimpmode_ctxt = { &wimpmode_data, NULL, 0, 0 };
const volatile wimpmode_state *const wimpmode = &wimpmode_data;

static event_rspcode wimpmode_event(void *statev, wimp_eventtype t, void *data)
{
  struct wimpmode_ctxt *state = statev;
  wimp_msghdr *hdr = data;
  if (t == wimp_User_Message && hdr->action == wimp_Message_ModeChange) {
    if (mode_getgeom(&state->st->geom) < 0) {
      state->st->err = *task_err();
      task_seterr(NULL);
    }
    if (wimpmode_ctxt.ufp) (*wimpmode_ctxt.ufp)(wimpmode_ctxt.ud);
  }
  return event_SHIRK;
}

int wimpmode_init(void (*fp)(void *), void *ud)
{
  wimp_msgtype msgtypes[] = { wimp_Message_ModeChange, 0 };
  if (!wimpmode_ctxt.eh) {
    wimpmode_ctxt.eh = event_setpre(&wimpmode_event, &wimpmode_ctxt);
    wimpmsg_accept(msgtypes);
    event_select((1<<wimp_User_Message) |
                 (1<<wimp_User_Message_Recorded));
  }
  wimpmode_ctxt.ufp = fp;
  wimpmode_ctxt.ud = ud;
  if (mode_getgeom(&wimpmode_ctxt.st->geom) < 0) {
    wimpmode_ctxt.st->err = *task_err();
    return -1;
  }
  if (wimpmode_ctxt.ufp) (*wimpmode_ctxt.ufp)(wimpmode_ctxt.ud);
  return -0;
}

void wimpmode_term(void)
{
  wimp_msgtype msgtypes[2] = { wimp_Message_ModeChange, 0 };
  if (wimpmode_ctxt.eh) {
    wimpmsg_reject(msgtypes);
    event_cancel(wimpmode_ctxt.eh);
    wimpmode_ctxt.eh = NULL;
    event_deselect((1<<wimp_User_Message) |
                   (1<<wimp_User_Message_Recorded));
  }
}
