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
#include "../riscos/wimp/key.h"
#include "../riscos/wimp/icon.h"
#include "../riscos/wimp/win.h"

#include "../yacitros/desktop/shutdown.h"
#include "../yacitros/desktop/wimpmsg.h"
#include "../yacitros/desktop/task.h"
#include "../yacitros/desktop/event.h"

#include "throw.h"

typedef struct {
  event_ref eh;
  shutdown_proc *func;
  void *ctxt;
  wimp_taskhandle initiator;
} shutdown_context_type;

static shutdown_context_type shutdown_context;

static event_rspcode shutdown_events(void *cv, wimp_eventtype et, void *hdrv)
{
  shutdown_context_type *c = cv;
  wimp_msghdr *hdr = hdrv;

  switch (et) {
  case wimp_User_Message:
  case wimp_User_Message_Recorded:
    break;
  default:
    return event_SHIRK;
  }
  if (hdr->action != wimp_Message_PreQuit)
    return event_SHIRK;
  if (c->func && (*c->func)(c->ctxt)) {
    hdr->your_ref = hdr->my_ref;
    THROWE(wimp_sendmessage_totask
           (wimp_User_Message_Acknowledge, hdr, hdr->sender));
    c->initiator = hdr->sender;
  }
  return event_CLAIM;
}

void shutdown_config(shutdown_proc *f, void *c)
{
  wimp_msgtype messages[] = { wimp_Message_PreQuit, 0 };

  shutdown_context.func = f;
  shutdown_context.ctxt = c;

  if (shutdown_context.func && !shutdown_context.eh) {
    event_select((1<<wimp_User_Message) |
                 (1<<wimp_User_Message_Recorded));
    shutdown_context.eh = event_setpre(&shutdown_events, &shutdown_context);
    wimpmsg_accept(messages);
  } else if (!shutdown_context.func && shutdown_context.eh) {
    wimpmsg_reject(messages);
    event_cancel(shutdown_context.eh);
    shutdown_context.eh = NULL;
    event_deselect((1<<wimp_User_Message) |
                   (1<<wimp_User_Message_Recorded));
  }
}

int shutdown_restart(void)
{
  wimp_keypressedevent ke;

  if (!shutdown_context.initiator)
    return 0;

  ke.wh = wimp_WBACKGROUND;
  ke.ih = wimp_IWORKAREA;
  ke.key = wimp_KF12 | wimp_KCTRL | wimp_KSHIFT;
  THROW(wimp_sendmessage_totask(wimp_Key_Pressed, &ke,
                                shutdown_context.initiator));
  return 0;
}
