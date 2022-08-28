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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../riscos/wimp/op.h"
#include "../riscos/wimp/msgtypes.h"
#include "../riscos/wimp/event.h"

#include "../yacitros/desktop/transmit.h"
#include "../yacitros/desktop/event.h"
#include "../yacitros/desktop/wimpmsg.h"
#include "../yacitros/desktop/task.h"
#include "../yacitros/desktop/dataxfer.h"

#include "throw.h"

static event_rspcode transmit_send_events(void *, wimp_eventtype, void *);

int transmit_open(transmit_record *r,
                  const char *name, ptrdiff_t sz, file_type type,
                  const vdu_point *pos,
                  wimp_winhandle wh, wimp_iconhandle ih,
                  void *ctxt, transmit_depositproc *d,
                  transmit_supplyproc *s)
{
  wimp_msgtype messages[] = {
    wimp_Message_DataSave, wimp_Message_DataSaveAck,
    wimp_Message_DataLoad, wimp_Message_DataLoadAck,
    wimp_Message_RAMFetch, wimp_Message_RAMTransmit, 0
  };
  dataxfer_msgblock block;

  r->ctxt = ctxt;
  r->deposit = d;
  r->supply = s;

  block.body.file.size = sz;
  block.body.file.type = type;
  block.body.file.ih = ih;
  block.body.file.wh = wh;
  block.body.file.pos = *pos;
  strncpy(block.body.file.name, name, sizeof block.body.file.name);

  block.hdr.action = wimp_Message_DataSave;
  block.hdr.your_ref = wimp_msgref_NONE;
  dataxfer_limmsg(&block);
  THROW(wimp_sendmessage_towindow
        (wimp_User_Message_Recorded, &block, wh, ih, NULL));
  r->lastref = block.hdr.my_ref;

  if (r->eh)
    return 0;
  r->eh = event_setpre(&transmit_send_events, r);
  wimpmsg_accept(messages);
  event_select((1<<wimp_User_Message) |
               (1<<wimp_User_Message_Recorded) |
               (1<<wimp_User_Message_Acknowledge));
  return 0;
}

void transmit_close(transmit_record *r)
{
  if (r->eh) {
    wimp_msgtype messages[] = {
      wimp_Message_DataSave, wimp_Message_DataSaveAck,
      wimp_Message_DataLoad, wimp_Message_DataLoadAck,
      wimp_Message_RAMFetch, wimp_Message_RAMTransmit, 0
    };

    wimpmsg_reject(messages);
    event_deselect((1<<wimp_User_Message) |
                   (1<<wimp_User_Message_Recorded) |
                   (1<<wimp_User_Message_Acknowledge));

    event_cancel(r->eh);
    r->eh = NULL;
  }
}

static event_rspcode transmit_send_events(void *rv,
                                          wimp_eventtype et, void *bptrv)
{
  transmit_record *r = rv;
  dataxfer_msgblock *bptr = bptrv;

  switch (et) {
  case wimp_User_Message:
  case wimp_User_Message_Recorded:
    switch (bptr->hdr.action) {
    case wimp_Message_RAMFetch:
      if (bptr->hdr.your_ref != r->lastref)
        return event_SHIRK;
      if (r->supply) {
#if 0
        size_t oldlen = bptr->body.mem.len;
#endif
        void *data = (*r->supply)(r->ctxt, &bptr->body.mem.len);

        if (task_seterr(wimp_transferblock(task_gethandle(),
                                           data, bptr->hdr.sender,
                                           bptr->body.mem.buffer,
                                           bptr->body.mem.len)) ||
            task_seterr(wimp_sendmessage_totask(wimp_User_Message,
                                                bptr, bptr->hdr.sender)))
          transmit_close(r);
      }
      return event_CLAIM;

    case wimp_Message_DataSaveAck:
      if (bptr->hdr.your_ref != r->lastref)
        return event_SHIRK;
      if (!r->deposit)
        return event_SHIRK;
      if (!(*r->deposit)(r->ctxt, (char *) bptr->body.file.name,
                         bptr->body.file.size >= 0)) {
        transmit_close(r);
        return event_CLAIM;
      }
      bptr->hdr.your_ref = bptr->hdr.my_ref;
      bptr->hdr.action = wimp_Message_DataLoad;
      if (task_seterr(wimp_sendmessage_totask(wimp_User_Message_Recorded,
                                              bptr, bptr->hdr.sender))) {
        transmit_close(r);
        return event_CLAIM;
      }
      r->lastref = bptr->hdr.my_ref;
      return event_CLAIM;
    case wimp_Message_DataLoadAck:
      if (bptr->hdr.your_ref != r->lastref)
        return event_SHIRK;
      if (bptr->body.file.size < 0)
        remove((char *) bptr->body.file.name);
      transmit_close(r);
      return event_CLAIM;
    default:
      return event_SHIRK;
    }

  case wimp_User_Message_Acknowledge:
    switch (bptr->hdr.action) {
    case wimp_Message_DataSave:
    case wimp_Message_DataLoad:
    case wimp_Message_RAMTransmit:
      if (bptr->hdr.your_ref != r->lastref)
        return event_SHIRK;
      if (bptr->hdr.action == wimp_Message_DataLoad &&
          bptr->body.file.size < 0)
        remove(bptr->body.file.name);
      transmit_close(r);
      return event_CLAIM;
    default:
      return event_SHIRK;
    }
  default:
    return event_SHIRK;
  }
}
