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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>
#include <assert.h>

#include <ddslib/dllist.h>

#include "../riscos/wimp/op.h"
#include "../riscos/wimp/msgtypes.h"
#include "../riscos/wimp/event.h"

#include "../yacitros/desktop/menu.h"
#include "../yacitros/desktop/event.h"
#include "../yacitros/desktop/help.h"
#include "../yacitros/desktop/wimpmsg.h"
#include "../yacitros/desktop/task.h"

#include "../utils.h"
#include "throw.h"

int menu_parse(const char *);
int menu_fill(menu_handle, const char *);
menu_handle menu_reserve(const char *title, int width, int max_items);

int menu_parse(const char *fmt)
{
  int n = 0;
  int s = 0;

  while (*fmt) {
    if (s) {
      switch (*fmt) {
      case ' ':
      case '!':
      case '~':
      case '>':
        break;
      case ',':
      case '|':
        n++;
        break;
      default:
        s = 1;
        break;
      }
    } else {
      if (*fmt == ',' || *fmt == '|') {
        s = 0;
        n++;
      }
    }
    fmt++;
  }
  return n + 1;
}

static void remove_indirected(menu_handle m)
{
  size_t n = 0;
  wimp_menuitem *ip;

  /* Detect and free an indirected title. */
  if (wimp_menuitems(m)[0].menu_flags.bits.indir_title)
    free(m->title.indirected_text.buffer);

  /* Detect and free indirected, non-writable text items. */
  do {
    ip = &wimp_menuitems(m)[n];
    if (ip->flags.bits.indirected && ip->flags.bits.text &&
        !ip->menu_flags.bits.writeable)
      free(ip->data.indirected_text.buffer);
    n++;
  } while (!ip->menu_flags.bits.last);
}

static size_t my_mbsnlen(const char *s, size_t maxlen)
{
  size_t r = 0;
  static const mbstate_t initial_state;
  mbstate_t st = initial_state;

  while (*s) {
    size_t cl = mbrlen(s, maxlen, &st);
    if (cl == (size_t) -1)
      return r;
    if (cl == (size_t) -2)
      return r;

    r++;
    s += cl;
    maxlen -= cl;
  }

  return r;
}

static inline size_t my_mbslen(const char *s)
{
  return my_mbsnlen(s, (size_t) -1);
}

static int load_string(wimp_menuitem *ip, size_t *max,
                       const char *start, const char *end)
{
  assert(start);
  assert(end);

  size_t clen = my_mbsnlen(start, end - start);
  size_t len = end - start;
  if (clen > *max) *max = clen;

  if (len > sizeof ip->data.text) {
    char *buf = malloc(len + 1);
    if (!buf) return -1;
    memcpy(buf, start, len);
    buf[len] = '\0';
    ip->flags.bits.indirected = true;
    ip->data.indirected_text.buffer = buf;
    ip->data.indirected_text.val = NULL;
    ip->data.indirected_text.buflen = len + 1;
  } else {
    memset(ip->data.text, 0, sizeof ip->data.text);
    strncpy(ip->data.text, start, len);
    ip->flags.bits.indirected = false;
  }
  return 0;
}

int menu_fill(menu_handle m, const char *fmt)
{
  const char *text_start = NULL;
  int n = 0; /* item number */
  int s = 0; /* non-zero => in label */
  size_t w;

  /* Use the title length as the initial minimum width. */
  if (wimp_menuitems(m)[0].menu_flags.bits.indir_title) {
    w = my_mbsnlen(m->title.indirected_text.buffer,
                   m->title.indirected_text.buflen);
  } else {
    w = my_mbsnlen(m->title.text, sizeof m->title.text);
  }

  wimp_menuitems(m)[n].menu_flags.bits.last = false;
  while (*fmt) {
    if (!s) {
      switch (*fmt) {
      case ' ':
        break;

      case '!':
        menu_tick(m, n, true);
        break;

      case '~':
        menu_select(m, n, false);
        break;

      case '>':
        menu_warn(m, n, true);
        wimp_menuitems(m)[n].sub.wh = 1;
        break;

      case '|':
        menu_dotted(m, n, true);
      case ',':
        wimp_menuitems(m)[n].menu_flags.bits.last = false;
        break;

      default:
        text_start = fmt;
        s = 1;
        break;
      }
    } else {
      switch (*fmt) {
      case '|':
        menu_dotted(m, n, true);
      case ',':
        wimp_menuitems(m)[n].menu_flags.bits.last = false;
        if (load_string(&wimp_menuitems(m)[n], &w, text_start, fmt) < 0) {
          remove_indirected(m);
          return -1;
        }
        text_start = NULL;
        n++;
        s = 0;
        break;

      default:
        break;
      }
    }
    fmt++;
  }
  wimp_menuitems(m)[n].menu_flags.bits.last = true;
  if (text_start) {
    if (load_string(&wimp_menuitems(m)[n], &w, text_start, fmt) < 0) {
      remove_indirected(m);
      return -1;
    }
  }

  m->item_width = 16 * (w + 1);

  return n;
}

menu_handle menu_create(const char *title, const char *fmt)
{
  int len = menu_parse(fmt);
  menu_handle m = menu_reserve(title, 12, len);
  if (!m) return NULL;
  if (menu_fill(m, fmt) < 0) {
    free(m);
    return NULL;
  }
  return m;
}

void menu_destroy(menu_handle m)
{
  if (!m) return;
  remove_indirected(m);
  free(m);
}

void menu_destroytree(menu_handle m)
{
  int i;
  for (i = 0; !wimp_menuitems(m)[i].menu_flags.bits.last; i++)
    if (wimp_menuitems(m)[i].sub.word != wimp_NOSUBMENU &&
        wimp_menuitems(m)[i].sub.word >= 0x8000u)
      menu_destroytree(wimp_menuitems(m)[i].sub.menu);
  menu_destroy(m);
}


menu_handle menu_reserve(const char *title, int width, int max_items)
{
  /* A menu must have at least one item, otherwise we can't detect the
     'last' or 'indir_title' flags in the first item. */
  if (max_items < 1) return NULL;

  int i;
  menu_handle h = malloc(wimp_menusize(max_items));

  if (!h) return NULL;
  size_t tlen = strlen(title);
  bool indir = tlen > sizeof h->title.text;
  if (indir) {
    char *buf = malloc(tlen + 1);
    if (!buf) {
      free(h);
      return NULL;
    }
    strncpy(buf, title, tlen + 1);
    h->title.indirected_text.buffer = buf;
    h->title.indirected_text.buflen = tlen + 1;
    h->title.indirected_text.val = NULL;
  } else {
    strncpy(h->title.text, title, sizeof h->title.text);
  }
  h->title_fg = 7;
  h->title_bg = 2;
  h->work_fg = 7;
  h->work_bg = 0;
  h->item_width = 16 * width;
  h->item_height = 44;
  h->item_gap = 0;

  for (i = 0; i < max_items; i++) {
    wimp_menuitem *ip = wimp_menuitems(h) + i;
    ip->menu_flags.word = 0;
    ip->sub.word = wimp_NOSUBMENU;
    ip->flags.word = 0x07000031; /* 00000111 00000000 00000000 00110001 */
    strncpy(ip->data.text, "<Unset>", 12);
  }
  wimp_menuitems(h)[max_items - 1].menu_flags.bits.last = true;
  if (indir)
    wimp_menuitems(h)[0].menu_flags.bits.indir_title = true;

  return h;
}

int menu_attachsubmenu(menu_handle h, int ino, menu_handle sub)
{
  wimp_menuitems(h)[ino].sub.menu = sub;
  return 0;
}

int menu_attachsubwindow(menu_handle h, int ino, wimp_winhandle sub)
{
  wimp_menuitems(h)[ino].sub.wh = sub & 0x7fffu;
  return 0;
}

int menu_warn(menu_handle h, int ino, int val)
{
  wimp_menuitems(h)[ino].menu_flags.bits.message = val;
  return 0;
}

int menu_tick(menu_handle h, int ino, int val)
{
  wimp_menuitems(h)[ino].menu_flags.bits.tick = val;
  return 0;
}

int menu_select(menu_handle h, int ino, int val)
{
  wimp_menuitems(h)[ino].flags.bits_colour.disabled = !val;
  return 0;
}

int menu_dotted(menu_handle h, int ino, int val)
{
  wimp_menuitems(h)[ino].menu_flags.bits.dotted = val;
  return 0;
}

#if 0
int menu_setlength(menu_handle h, int ino)
{
  int i;
  for (i = 0; i < ino; i++)
    wimp_menuitems(h)[i].menu_flags.bits.last = (i == ino - 1);
  return 0;
}
#endif

static int menu_setdata_static(menu_handle h, int ino, const char s[12])
{
  wimp_menuitem *ip = &wimp_menuitems(h)[ino];
  if (ip->flags.bits_colour.indirected && !ip->menu_flags.bits.writeable)
    free(ip->data.indirected_text.buffer);
  strncpy(ip->data.text, s, sizeof ip->data.text);
  ip->flags.bits_colour.indirected = false;
  ip->menu_flags.bits.writeable = false;
  return 0;
}

static int menu_setdata_indirected(menu_handle h, int ino,
                                   const char *s, size_t n)
{
  wimp_menuitem *ip = &wimp_menuitems(h)[ino];
  char *buffer;
  if (ip->flags.bits_colour.indirected && !ip->menu_flags.bits.writeable) {
    buffer = realloc(ip->data.indirected_text.buffer, n);
  } else {
    buffer = malloc(n);
  }
  if (!buffer) return -1;
  strncpy(buffer, s, n);
  ip->data.indirected_text.buffer = buffer;
  ip->data.indirected_text.buflen = n;
  ip->data.indirected_text.val = NULL;
  ip->flags.bits_colour.indirected = true;
  ip->menu_flags.bits.writeable = false;
  return 0;
}

int menu_setdata(menu_handle h, int ino, const char *s)
{
  size_t len = strlen(s);
  if (len > sizeof wimp_menuitems(h)[ino].data.text)
    return menu_setdata_indirected(h, ino, s, len);
  else
    return menu_setdata_static(h, ino, s);
}

int menu_setdata_writeable(menu_handle h, int ino, char *s, const char *val,
                           size_t n)
{
  wimp_menuitem *ip = &wimp_menuitems(h)[ino];
  if (ip->flags.bits_colour.indirected && !ip->menu_flags.bits.writeable)
    free(ip->data.indirected_text.buffer);
  ip->data.indirected_text.buffer = s;
  ip->data.indirected_text.buflen = n;
  ip->data.indirected_text.val = (char *) val;
  ip->flags.bits_colour.indirected = true;
  ip->menu_flags.bits.writeable = true;
  return 0;
}

vdu_ord menu_height(menu_handle h)
{
  int i = 0, rules = 0;
  while (rules += wimp_menuitems(h)[i].menu_flags.bits.dotted,
         !wimp_menuitems(h)[i++].menu_flags.bits.last)
    ;
  return h->item_height * i + rules * 24;
}

struct menu_state {
  menu_genproc *gen;
  menu_selproc *sel;
  menu_warnproc *op;
  menu_helpproc *help;
  void *handle;
  event_ref eh;
  wimp_winhandle nohelp;
  bool msgs;
};

struct menu_state menu_context;

struct menu_msgblock {
  wimp_msghdr hdr;
  union {
    struct {
      void *submenu;
      vdu_point pos;
      wimp_menuchoice selection[1];
    } warning;
  } body;
};

union menu_event {
  struct menu_msgblock msg;
  help_msgblock help;
  wimp_menuchoice selection[1];
};

void menu_dereg(void);

static event_rspcode menu_eventproc(void *hv, wimp_eventtype et, void *datav)
{
  struct menu_state *h = hv;
  union menu_event *data = datav;
  wimp_mouseevent mev;
  wimp_menuchoice decoded[30];
  const char *helptext;

#if 0
  task_error(0, "menu_eventproc(%p,%p,%p,%p)",
             (void *) h->gen,
             (void *) h->sel,
             (void *) h->op,
             (void *) h->help);
#endif

  switch (et) {
  case wimp_Menu_Selection:
    THROWE(wimp_getpointerinfo(&mev));
    if (h->sel) (*h->sel)(h->handle, data->selection);
    if (h->gen && mev.mouse.buttons.bits.adjust0)
      task_seterr(wimp_createmenu
                  ((*h->gen)(h->handle, mev.wh, mev.ih, NULL), 0, 0));
    return event_CLAIM;
  case wimp_User_Message:
  case wimp_User_Message_Recorded:
    switch (data->msg.hdr.action) {
    case wimp_Message_MenuWarning:
      if (h->op) (*h->op)(h->handle, data->msg.body.warning.selection,
                          &data->msg.body.warning.pos);
      return event_CLAIM;
    case wimp_Message_HelpRequest:
      if (data->help.body.req.wh == h->nohelp)
        return event_SHIRK;
      THROWE(wimp_getmenustate
             (data->help.body.req.wh, data->help.body.req.ih, decoded));
      if (decoded[0] == -1)
        return event_SHIRK;
      helptext = (h->help) ? (*h->help)(h->handle, decoded) : NULL;
      if (helptext) {
        data->help.hdr.action = wimp_Message_HelpReply;
        data->help.hdr.your_ref = data->help.hdr.my_ref;
        strncpy(data->help.body.rep.text, helptext, 236);
        help_delimitmsg(&data->help);
        task_seterr(wimp_sendmessage_totask(wimp_User_Message, data,
                                            data->help.hdr.sender));
        return event_CLAIM;
      }
      return event_SHIRK;
    case wimp_Message_MenusDeleted:
      menu_dereg();
      return event_CLAIM;
    default:
      return event_SHIRK;
    }
  }
  return event_SHIRK;
}

int menu_openwin(wimp_winhandle wh, vdu_ord x, vdu_ord y)
{
  menu_context.nohelp = wh;
  THROW(wimp_closemenu());
  THROW(wimp_createmenuwindow(wh, x, y));
  return 0;
}

int menu_opensubwin(wimp_winhandle wh, vdu_ord x, vdu_ord y)
{
  menu_context.nohelp = wh;
  THROW(wimp_createsubmenuwindow(wh, x, y));
  return 0;
}

int menu_open(wimp_winhandle wh, wimp_iconhandle ih, const vdu_point *posp,
              menu_genproc *g, menu_selproc *f,
              menu_warnproc *f2, menu_helpproc *f3, void *fh)
{
  vdu_point pos;
  menu_handle mh;

  menu_context.gen = g;
  menu_context.sel = f;
  menu_context.op = f2;
  menu_context.help = f3;
  menu_context.handle = fh;

#if 0
  task_error(0, "menu_open(%p,%p,%p,%p)",
             (void *) menu_context.gen,
             (void *) menu_context.sel,
             (void *) menu_context.op,
             (void *) menu_context.help);
#endif

  if (!menu_context.eh) {
    wimp_msgtype msglist[] = {
      wimp_Message_MenuWarning,
      wimp_Message_MenusDeleted,
      wimp_Message_HelpRequest,
      0
    };
    menu_context.eh =
      event_setpost(&menu_eventproc, &menu_context);
    event_select((1<<wimp_Menu_Selection) |
                 (1<<wimp_User_Message) |
                 (1<<wimp_User_Message_Recorded));
    // TODO: Make wimpmsg_accept return oserror(?), and use it.
    if (wimpmsg_accept(msglist) < 0) {
      event_cancel(menu_context.eh), menu_context.eh = NULL;
      menu_dereg();
      return -1;
    }
  }
  pos = *posp;
  mh = (*menu_context.gen)(menu_context.handle, wh, ih, &pos);
  menu_context.nohelp = (wimp_winhandle) mh;
  if (task_seterr(wimp_createmenu(mh, pos.x, pos.y))) {
    menu_dereg();
    return -1;
  }

  return 0;
}


int menu_openfromevent(const wimp_mouseevent *me, menu_genproc *g,
                       menu_selproc *f, menu_warnproc *f2,
                       menu_helpproc *f3, void *fh)
{
  return menu_open(me->wh, me->ih, &me->mouse.pos, g, f, f2, f3, fh);
}

#if 0
void menu_openfromevent(const wimp_mouseevent *me, menu_genproc *g,
                        menu_selproc *f, menu_warnproc *f2,
                        menu_helpproc *f3, void *fh)
{
  vdu_point pos;
  menu_handle mh;

  menu_context.gen = g;
  menu_context.sel = f;
  menu_context.op = f2;
  menu_context.help = f3;
  menu_context.handle = fh;
  if (!menu_context.eh) {
    wimp_msgtype msglist[] = {
      wimp_Message_MenuWarning,
      wimp_Message_MenusDeleted,
      wimp_Message_HelpRequest,
      0
    };
    menu_context.eh =
      event_setpost(&menu_eventproc, &menu_context);
    event_select((1<<wimp_Menu_Selection) |
                 (1<<wimp_User_Message) |
                 (1<<wimp_User_Message_Recorded));
    wimpmsg_accept(msglist);
  }
  pos = me->mouse.pos;
  mh = (*menu_context.gen)(menu_context.handle, me->wh, me->ih, &pos);
  menu_context.nohelp = (wimp_winhandle) mh;
  wimp_createmenu(mh, pos.x, pos.y);
}
#endif

int menu_opensub(menu_handle h, vdu_ord x, vdu_ord y)
{
  menu_context.nohelp = (wimp_winhandle) h;
  return task_seterr(wimp_createsubmenu(h, x, y)) ? -1 : 0;
}

void menu_close(void)
{
  // We should do nothing if we don't own the current menu.
  if (menu_context.gen) {
    // Try to close the menu, but if we get an error, it probably
    // makes no difference if we try to handle it.
    IGNORE(wimp_closemenu());
    menu_dereg();
  }
}

void menu_dereg(void)
{
  menu_context.gen = NULL;
  if (menu_context.eh) {
    wimp_msgtype msglist[] = {
      wimp_Message_MenuWarning,
      wimp_Message_MenusDeleted,
      wimp_Message_HelpRequest,
      0
    };
    event_cancel(menu_context.eh);
    menu_context.eh = NULL;
    event_deselect((1<<wimp_Menu_Selection) |
                   (1<<wimp_User_Message) |
                   (1<<wimp_User_Message_Recorded));
    wimpmsg_reject(msglist);
  }
}

struct menu_attachmentstr {
  wimp_winhandle wh;
  event_ref reg;
  struct {
    void *handle;
    menu_genproc *gen;
    menu_selproc *sel;
    menu_warnproc *op;
    menu_helpproc *help;
  } user;
};

static event_rspcode menu_attachproc(void *attv, wimp_eventtype et,
                                     void *datav)
{
  struct menu_attachmentstr *att = attv;
  wimp_mouseevent *data = datav;

  switch (et) {
  case wimp_Mouse_Click:
    if (att->wh == data->wh)
      if (data->mouse.buttons.bits.menu0) {
        IGNOREI(menu_openfromevent(data, att->user.gen, att->user.sel,
                                   att->user.op, att->user.help,
                                   att->user.handle));
        return event_CLAIM;
      }
  }
  return event_SHIRK;
}

menu_attachment menu_attach(wimp_winhandle wh, menu_genproc *gen,
                            menu_selproc *sel, menu_warnproc *op,
                            menu_helpproc *help, void *handle)
{
  struct menu_attachmentstr *ALLOCATE(rp);
  if (!rp)
    return NULL;
  rp->wh = wh;
  rp->user.handle = handle;
  rp->user.gen = gen;
  rp->user.sel = sel;
  rp->user.op = op;
  rp->user.help = help;
  rp->reg = event_setpre(&menu_attachproc, rp);
  if (!rp->reg) {
    free(rp);
    return NULL;
  }
  return rp;
}

void menu_detach(menu_attachment ah)
{
  if (!ah) return;
  event_cancel(ah->reg);
  free(ah);
}
