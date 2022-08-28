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

#include "wincommon.h"
#include "throw.h"

event_rspcode win_eventproc(void *rv, wimp_eventtype et, void *datav)
{
  win_handle r = rv;
  win_msgs *data = datav;
  switch (et) {
  case wimp_Redraw_Window_Request:
    if (win_matchhandle(r, data->wh)) {
      int more;
      wimp_rectangleblock block;

      block.wh = r->wh;
      THROWE(wimp_redrawwindow(&block, &more));
      while (more) {
        wimp_screen2work_area(&block.rect.dim, &block.rect.clip,
                              &block.rect.clip);
        if (r->user.redraw)
          (*r->user.redraw)(r->user.handle, &block.rect.dim,
                            &block.rect.clip);
        task_seterr(wimp_getrectangle(&block, &more));
      }
      return event_CLAIM;
    }
    break;
  case wimp_Open_Window_Request:
    if (!r->user.open) break;
    if (win_matchhandle(r, data->owr.wh))
      return (*r->user.open)(r->user.handle, &data->owr.loc);
    break;
  case wimp_Close_Window_Request:
    if (!r->user.close) break;
    if (win_matchhandle(r, data->wh))
      return (*r->user.close)(r->user.handle);
    break;
  case wimp_Pointer_Leaving_Window:
    if (!r->user.ptrout) break;
    if (win_matchhandle(r, data->wh))
      return (*r->user.ptrout)(r->user.handle);
    break;
  case wimp_Pointer_Entering_Window:
    if (!r->user.ptrin) break;
    if (win_matchhandle(r, data->wh))
      return (*r->user.ptrin)(r->user.handle);
    break;
  case wimp_Mouse_Click:
    if (!r->user.click) break;
    if (win_matchhandle(r, data->me.wh)) {
#if 0
      _swix(0x104, 0);
      printf("win: datav=%p, data=%p &x=%p", datav, (void *) data,
             (void *) &data->me.mouse.pos.x);
      _swix(0x105, 0);
      task_error(0, "win: datav=%p, data=%p &x=%p &x=%p",
                 datav, (void *) data,
                 (void *) &data->me.mouse.pos.x,
                 (void *) &(data->me.mouse.pos.x));
#endif
      return (*r->user.click)(r->user.handle, &data->me.mouse, data->me.ih);
    }
    break;
  case wimp_Key_Pressed:
    if (!r->user.key) break;
    if (win_matchhandle(r, data->kpe.wh))
      return (*r->user.key)(r->user.handle, &data->kpe.caret, data->kpe.ih,
                            data->kpe.key);
    break;
  case wimp_Scroll_Request:
    if (!r->user.scroll) break;
    if (win_matchhandle(r, data->sr.current.wh))
      return (*r->user.scroll)(r->user.handle, &data->sr.current.loc,
                               &data->sr.change);
    break;
  case wimp_Lose_Caret:
    if (!r->user.caretout) break;
    if (win_matchhandle(r, data->ce.wh))
      return (*r->user.caretout)(r->user.handle, &data->ce.pos, data->ce.ih);
    break;
  case wimp_Gain_Caret:
    if (!r->user.caretin) break;
    if (win_matchhandle(r, data->ce.wh))
      return (*r->user.caretin)(r->user.handle, &data->ce.pos, data->ce.ih);
    break;
  case wimp_User_Message_Acknowledge:
    switch (data->xfer.hdr.action) {
    case wimp_Message_RAMFetch:
      if (data->xfer.hdr.my_ref != r->saveref)
        return event_SHIRK;
      if (r->xferfail) {
        if (r->user.resv)
          (*r->user.resv)(r->user.handle, NULL);
      } else {
        r->savemsg.hdr.your_ref = r->savemsg.hdr.my_ref;
        r->savemsg.hdr.action = wimp_Message_DataSaveAck;
        r->savemsg.body.file.size = -1;
        dataxfer_limmsg(&r->savemsg);
        task_seterr(wimp_sendmessage_totask
                    (wimp_User_Message, &r->savemsg, r->savemsg.hdr.sender));
        r->saveref = wimp_msgref_NONE;
        return event_CLAIM;
      }
      return event_CLAIM;
    }
    break;
  case wimp_User_Message:
  case wimp_User_Message_Recorded:
    switch (data->xfer.hdr.action) {
    case wimp_Message_HelpRequest:
      if (win_matchhandle(r, data->help.body.req.wh) && r->user.help) {
        const char *msg = (*r->user.help)(r->user.handle,
                                          &data->help.body.req.ms,
                                          data->help.body.req.ih);
        if (msg) {
          data->help.hdr.action = wimp_Message_HelpReply;
          data->help.hdr.your_ref = data->help.hdr.my_ref;
          strncpy(data->help.body.rep.text, msg, 236);
          help_delimitmsg(&data->help);
          task_seterr(wimp_sendmessage_totask
                      (wimp_User_Message, data, data->help.hdr.sender));
          return event_CLAIM;
        }
        return event_SHIRK;
      }
      return event_SHIRK;
    case wimp_Message_DataLoad:
      if (!win_matchhandle(r, data->xfer.body.file.wh))
        return event_SHIRK;
      if (r->user.load &&
          (*r->user.load)(r->user.handle, data->xfer.body.file.ih,
                          &data->xfer.body.file.pos,
                          data->xfer.body.file.size,
                          data->xfer.body.file.type,
                          data->xfer.body.file.name)) {
        data->xfer.hdr.your_ref = data->xfer.hdr.my_ref;
        data->xfer.hdr.action = wimp_Message_DataLoadAck;
        task_seterr(wimp_sendmessage_totask
                    (wimp_User_Message, data, data->xfer.hdr.sender));
        return event_CLAIM;
      }
      break;
    case wimp_Message_DataSave:
      if (!win_matchhandle(r, data->xfer.body.file.wh))
        return event_SHIRK;
      if (!r->user.save)
        return event_SHIRK;
      if ((*r->user.save)(r->user.handle, data->xfer.body.file.ih,
                          &data->xfer.body.file.pos,
                          data->xfer.body.file.size,
                          data->xfer.body.file.type,
                          data->xfer.body.file.name,
                          sizeof data->xfer.body.file.name)) {
        data->xfer.hdr.action = wimp_Message_DataSaveAck;
        data->xfer.hdr.your_ref = data->xfer.hdr.my_ref;
        dataxfer_limmsg(&data->xfer);
        task_seterr(wimp_sendmessage_totask
                    (wimp_User_Message, data, data->xfer.hdr.sender));
        r->saveref = wimp_msgref_NONE;
        r->xferfail = false;
      } else if (r->user.filled && r->user.resv) {
        r->savemsg = data->xfer;
        data->xfer.hdr.action = wimp_Message_RAMFetch;
        data->xfer.hdr.your_ref = data->xfer.hdr.my_ref;
        data->xfer.body.mem.buffer =
          (*r->user.resv)(r->user.handle, &data->xfer.body.mem.len);
        dataxfer_limmsg(&data->xfer);
        task_seterr(wimp_sendmessage_totask
                    (wimp_User_Message_Recorded, data, data->xfer.hdr.sender));
        r->saveref = data->xfer.hdr.my_ref;
        r->xferfail = true;
      } else {
        data->xfer.hdr.action = wimp_Message_DataSaveAck;
        data->xfer.hdr.your_ref = data->xfer.hdr.my_ref;
        data->xfer.body.file.size = -1;
        dataxfer_limmsg(&data->xfer);
        task_seterr(wimp_sendmessage_totask
                    (wimp_User_Message, data, data->xfer.hdr.sender));
        r->saveref = wimp_msgref_NONE;
        r->xferfail = false;
      }
      return event_CLAIM;
    case wimp_Message_RAMTransmit:
      if (data->xfer.hdr.your_ref != r->saveref)
        return event_SHIRK;
      if (!r->user.filled)
        return event_SHIRK;
      (*r->user.filled)(r->user.handle, data->xfer.body.mem.len);
      r->xferfail = false;
      return event_CLAIM;
    }
  }
  return event_SHIRK;
}
