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

#define iconwin(H) ((H) == wimp_WICONBAR ? -1 : \
                    ((H) == wimp_WDEVICEBAR ? -2 : (H)))

int win_createicon(win_handle w,
                   const wimp_iconstate *id,
                   wimp_iconhandle *ip)
{
  wimp_createiconblock block;

  block.wh = iconwin(w->wh);
  block.i = *id;
  THROW(wimp_createicon(&block, ip));
  return 0;
}

int win_resizeicon(win_handle w, wimp_iconhandle ih, const vdu_box *b,
                   wimp_iconhandle *ip)
{
  wimp_iconstateblock is;
  wimp_createiconblock ci;

  is.wh = w->wh;
  is.ih = ih;
  THROW(wimp_geticonstate(&is));
  ci.wh = w->wh;
  ci.i = is.i;
  ci.i.bounds = *b;
  THROW(wimp_createicon(&ci, ip));
  THROW(wimp_deleteicon(w->wh, ih));
  return 0;
}

int win_geticonstate(win_handle w, wimp_iconhandle i, wimp_iconstate *id)
{
  wimp_iconstateblock block;
  block.wh = iconwin(w->wh);
  block.ih = i;
  THROW(wimp_geticonstate(&block));
  *id = block.i;
  return 0;
}

int win_deleteicon(win_handle w, wimp_iconhandle i)
{
  THROW(wimp_deleteicon(iconwin(w->wh), i));
  return 0;
}

int win_seticonflags(win_handle w, wimp_iconhandle i,
                     wimp_iconflags eor, wimp_iconflags clear)
{
  THROW(wimp_seticonstate(iconwin(w->wh), i, eor, clear));
  return 0;
}

int win_geticonflags(win_handle w, wimp_iconhandle i, wimp_iconflags *fl)
{
  wimp_iconstate id;

  THROWI(win_geticonstate(w, i, &id));

  *fl = id.flags;
  return 0;
}

int win_whichicon(win_handle w, wimp_iconhandle *is,
                  wimp_iconflags mask, wimp_iconflags test)
{
  THROW(wimp_whichicon(iconwin(w->wh), is, mask, test));
  return 0;
}

int win_dragiconpos(win_handle h,
                    drag_proc *f, void *d,
                    wimp_iconhandle ih)
{
  return drag_iconpos(f, d, h->wh, ih);
}

int win_iconselected(win_handle w, wimp_iconhandle i, int *s)
{
  wimp_iconflags st;
  int rc = win_geticonflags(w, i, &st);
  if (rc == 0) *s = st.bits_colour.selected;
  return rc;
}

int win_iconenabled(win_handle w, wimp_iconhandle i, int *s)
{
  wimp_iconflags st;
  int rc = win_geticonflags(w, i, &st);
  if (rc == 0) *s = !st.bits_colour.disabled;
  return rc;
}

int win_selecticon(win_handle w, wimp_iconhandle i, int s)
{
  wimp_iconflags eor, mask;
  eor.word = mask.word = 0;
  eor.bits_colour.selected = !!s;
  mask.bits_colour.selected = 1;
  return win_seticonflags(w, i, eor, mask);
}

int win_enableicon(win_handle w, wimp_iconhandle i, int s)
{
  wimp_iconflags eor, mask;
  eor.word = mask.word = 0;
  eor.bits_colour.disabled = !s;
  mask.bits_colour.disabled = 1;
  return win_seticonflags(w, i, eor, mask);
}

int win_setfield(win_handle r, wimp_iconhandle ih, const char *data)
{
  wimp_iconstate id;
  wimp_iconflags ef;
  char *buf;
  size_t lim;

  THROWI(win_geticonstate(r, ih, &id));
  if (!id.flags.bits_colour.text) STOP;
  if (id.flags.bits_colour.indirected) {
    lim = id.data.indirected_text.buflen;
    buf = id.data.indirected_text.buffer;
  } else {
    lim = sizeof id.data.text;
    buf = id.data.text;
  }
  strncpy(buf, data, lim);
  ef.word = 0;
  return win_seticonflags(r, ih, ef, ef);
}

int win_setfieldn(win_handle r, wimp_iconhandle ih,
                  const char *data, size_t n)
{
  wimp_iconstate id;
  wimp_iconflags ef;
  char *buf;
  size_t lim;

  THROWI(win_geticonstate(r, ih, &id));
  if (!id.flags.bits_colour.text) STOP;
  if (id.flags.bits_colour.indirected) {
    lim = id.data.indirected_text.buflen;
    buf = id.data.indirected_text.buffer;
  } else {
    lim = sizeof id.data.text;
    buf = id.data.text;
  }
  strncpy(buf, data, n < lim ? n : lim);
  if (n < lim)
    buf[n] = '\0';
  ef.word = 0;
  win_seticonflags(r, ih, ef, ef);
  return 0;
}

int win_setval(win_handle r, wimp_iconhandle ih, const char *data)
{
  wimp_iconstate id;
  wimp_iconflags ef;

  THROWI(win_geticonstate(r, ih, &id));
  if (!id.flags.bits_colour.text) STOP;
  if (!id.flags.bits_colour.indirected) STOP;
  strcpy(id.data.indirected_text.val, data);
  ef.word = 0;
  return win_seticonflags(r, ih, ef, ef);
}

int win_getfield(win_handle r, wimp_iconhandle ih, char *data, int len)
{
  wimp_iconstate id;
  char *c;
  int ilen, sz;

  if (len > 0) *data = '\0';
  THROWI(win_geticonstate(r, ih, &id));
  if (!id.flags.bits_colour.text) STOP;
  if (id.flags.bits_colour.indirected)
    c = id.data.indirected_text.buffer,
      ilen = id.data.indirected_text.buflen;
  else
    c = id.data.text, ilen = sizeof(id.data.text);

  sz = 0;
  while (sz < len - 1 && sz < ilen && *c >= 32 && *c != 127)
    sz++, *data++ = *c++;
  *data = '\0';
  return sz;
}

int win_setfield_int(win_handle r, wimp_iconhandle ih, int val)
{
  static char temp[100];
  snprintf(temp, sizeof temp, "%d", val);
  return win_setfield(r, ih, temp);
}

int win_getfield_int(win_handle r, wimp_iconhandle ih, int *val)
{
  static char temp[100];
  THROWI(win_getfield(r, ih, temp, sizeof(temp)));
  *val = atoi(temp);
  return 0;
}
