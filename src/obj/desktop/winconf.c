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

/* Configure a window abstraction */
void win_setcontext(win_handle r, void *h) { r->user.handle = h; }
void win_conf_redraw(win_handle r, win_redrawproc *f) { r->user.redraw = f; }
void win_conf_update(win_handle r, win_redrawproc *f) { r->user.update = f; }
void win_conf_click(win_handle r, win_clickproc *f) { r->user.click = f; }
void win_conf_key(win_handle r, win_keyproc *f) { r->user.key = f; }

void win_conf_open(win_handle r, win_openproc *f)
{
  win_openproc *of = r->user.open;
  r->user.open = f;
  if (!of && f) event_select(1<<wimp_Open_Window_Request);
  else if (of && !f) event_deselect(1<<wimp_Open_Window_Request);
}

void win_conf_close(win_handle r, win_closeproc *f)
{
  win_closeproc *of = r->user.close;
  r->user.close = f;
  if (!of && f) event_select(1<<wimp_Close_Window_Request);
  else if (of && !f) event_deselect(1<<wimp_Close_Window_Request);
}

void win_conf_scroll(win_handle r, win_scrollproc *f)
{
  win_scrollproc *of = r->user.scroll;
  r->user.scroll = f;
  if (!of && f) event_select(1<<wimp_Scroll_Request);
  else if (of && !f) event_deselect(1<<wimp_Scroll_Request);
}

void win_conf_caretin(win_handle r, win_caretmvproc *f)
{
  win_caretmvproc *of = r->user.caretin;
  r->user.caretin = f;
  if (!of && f) event_select(1<<wimp_Gain_Caret);
  else if (of && !f) event_deselect(1<<wimp_Gain_Caret);
}

void win_conf_caretout(win_handle r, win_caretmvproc *f)
{
  win_caretmvproc *of = r->user.caretout;
  r->user.caretout = f;
  if (!of && f) event_select(1<<wimp_Lose_Caret);
  else if (of && !f) event_deselect(1<<wimp_Lose_Caret);
}

void win_conf_ptrin(win_handle r, win_ptrmvproc *f)
{
  win_ptrmvproc *of = r->user.ptrin;
  r->user.ptrin = f;
  if (!of && f) event_select(1<<wimp_Pointer_Entering_Window);
  else if (of && !f) event_deselect(1<<wimp_Pointer_Entering_Window);
}

void win_conf_ptrout(win_handle r, win_ptrmvproc *f)
{
  win_ptrmvproc *of = r->user.ptrout;
  r->user.ptrout = f;
  if (!of && f) event_select(1<<wimp_Pointer_Leaving_Window);
  else if (of && !f) event_deselect(1<<wimp_Pointer_Leaving_Window);
}

void win_conf_load(win_handle r, win_loadproc *f)
{
  win_loadproc *of = r->user.load;
  wimp_msgtype messages[] = { wimp_Message_DataLoad, 0 };
  r->user.load = f;
  if (!of && f) {
    event_select((1<<wimp_User_Message) |
                 (1<<wimp_User_Message_Recorded));
    wimpmsg_accept(messages);
  } else if (of && !f) {
    event_deselect((1<<wimp_User_Message) |
                   (1<<wimp_User_Message_Recorded));
    wimpmsg_reject(messages);
  }
}

void win_conf_save(win_handle r, win_saveproc *f)
{
  win_saveproc *of = r->user.save;
  wimp_msgtype messages[] = { wimp_Message_DataSave, 0 };
  r->user.save = f;
  if (!of && f) {
    event_select((1<<wimp_User_Message) |
                 (1<<wimp_User_Message_Recorded));
    wimpmsg_accept(messages);
  } else if (of && !f) {
    event_deselect((1<<wimp_User_Message) |
                   (1<<wimp_User_Message_Recorded));
    wimpmsg_reject(messages);
  }
}

void win_conf_ramxfer(win_handle r, win_resvproc *resv,
                      win_filledproc *filled)
{
  int olds = !!r->user.save && !!r->user.resv && !!r->user.filled;
  int news;
  wimp_msgtype messages[] = {
    wimp_Message_RAMFetch,
    wimp_Message_RAMTransmit,
    0
  };
  r->user.resv = resv;
  r->user.filled = filled;
  news = !!r->user.save && !!r->user.resv && !!r->user.filled;
  if (news && !olds) {
    event_select((1<<wimp_User_Message) |
                 (1<<wimp_User_Message_Recorded |
                 (1<<wimp_User_Message_Acknowledge)));
    wimpmsg_accept(messages);
  } else if (olds && !news) {
    event_deselect((1<<wimp_User_Message) |
                   (1<<wimp_User_Message_Recorded) |
                   (1<<wimp_User_Message_Acknowledge));
    wimpmsg_reject(messages);
  }
}

void win_conf_help(win_handle r, win_helpproc *help)
{
  win_helpproc *of = r->user.help;
  wimp_msgtype messages[] = { wimp_Message_HelpRequest, 0 };
  r->user.help = help;
  if (!of && help) {
    event_select((1<<wimp_User_Message) |
                 (1<<wimp_User_Message_Recorded));
    wimpmsg_accept(messages);
  } else if (of && !help) {
    event_deselect((1<<wimp_User_Message) |
                   (1<<wimp_User_Message_Recorded));
    wimpmsg_reject(messages);
  }
}
