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

#include "../yacitros/desktop/menu.h"

#include "../utils.h"
#include "wincommon.h"

int win_openmenu(win_handle r, vdu_ord x, vdu_ord y)
{
  return menu_openwin(r->wh, x, y);
}

int win_opensubmenu(win_handle r, vdu_ord x, vdu_ord y)
{
  return menu_opensubwin(r->wh, x, y);
}

struct win_menuatstr {
  menu_attachment ma;
  void *h;
  win_menugenproc *f;
  win_menuselproc *ch;
  win_menuwarnproc *op;
  win_menuhelpproc *help;
};

static menu_handle win_menugen(void *rv,
                               wimp_winhandle wh,
                               wimp_iconhandle ih,
                               vdu_point *pos)
{
  win_menuat r = rv;

  if (!r || !r->f) return NULL;
  return (*r->f)(r->h, ih, pos);
}

static void win_menusel(void *rv, const wimp_menuchoice *c)
{
  win_menuat r = rv;
  if (r && r->ch) (*r->ch)(r->h, c);
}

static void win_menuop(void *rv, const wimp_menuchoice *c,
                       const vdu_point *p)
{
  win_menuat r = rv;
  if (r && r->op) (*r->op)(r->h, c, p);
}

static const char *win_menuhelp(void *rv, const wimp_menuchoice *c)
{
  win_menuat r = rv;
  return (r && r->help) ? (*r->help)(r->h, c) : NULL;
}

win_menuat win_attachmenu(win_handle w, win_menugenproc *gen,
                          win_menuselproc *sel, win_menuwarnproc *op,
                          win_menuhelpproc *help, void *handle)
{
  struct win_menuatstr *ALLOCATE(r);
  if (!r) return NULL;
  r->h = handle;
  r->f = gen;
  r->ch = sel;
  r->op = op;
  r->help = help;
  r->ma = menu_attach(w->wh, &win_menugen,
                      r->ch ? &win_menusel : NULL,
                      r->op ? &win_menuop : NULL,
                      r->help ? &win_menuhelp : NULL, r);
  if (!r->ma) {
    free(r);
    return NULL;
  }
  return r;
}

void win_detachmenu(win_menuat r)
{
  if (!r) return;
  menu_detach(r->ma);
  free(r);
}

struct win_iconmenu {
  void *handle;
  win_menugenproc *gen;
  win_menuselproc *sel;
  win_menuwarnproc *op;
  win_menuhelpproc *help;
};

static menu_handle win_iconmenu_gen(void *vh, wimp_winhandle wh,
                                    wimp_iconhandle ih, vdu_point *posp)
{
  struct win_iconmenu *h = vh;
  return h->gen ? (*h->gen)(h->handle, ih, posp) : NULL;
}

static void win_iconmenu_sel(void *vh, const wimp_menuchoice *mc)
{
  struct win_iconmenu *h = vh;
  if (h->sel)
    (*h->sel)(h->handle, mc);
}

static void win_iconmenu_op(void *vh, const wimp_menuchoice *mc,
                            const vdu_point *pos)
{
  struct win_iconmenu *h = vh;
  if (h->op)
    (*h->op)(h->handle, mc, pos);
}

static const char *win_iconmenu_help(void *vh, const wimp_menuchoice *mc)
{
  struct win_iconmenu *h = vh;
  return h->help ? (*h->help)(h->handle, mc) : NULL;
}

int win_openiconmenu(win_handle r,
                     wimp_iconhandle ih,
                     const vdu_point *posp,
                     win_menugenproc *gen,
                     win_menuselproc *sel,
                     win_menuwarnproc *op,
                     win_menuhelpproc *help,
                     void *handle)
{
  static struct win_iconmenu hd;

  hd.handle = handle;
  hd.gen = gen;
  hd.sel = sel;
  hd.op = op;
  hd.help = help;

  return menu_open(r->wh, ih, posp,
                   &win_iconmenu_gen,
                   &win_iconmenu_sel,
                   &win_iconmenu_op,
                   &win_iconmenu_help,
                   &hd);
}
