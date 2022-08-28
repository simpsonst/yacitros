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

#include <kernel.h>

#include "../utils.h"
#include "throw.h"
#include "wincommon.h"

/* Create a window from a template */
win_handle win_create(template_handle th, void *uh)
{
  wimp_winhandle wh;
  win_handle w;

  THROWN(wimp_createwindow(template_win(th), &wh));

  w = win_attach(wh, uh);
  if (!w) {
    IGNORE(wimp_deletewindow(wh));
    return NULL;
  }
  return w;
}

void win_destroy(win_handle h)
{
  if (h)
    IGNORE(wimp_deletewindow(win_detach(h)));
}

static void win_addpane(win_handle child, win_handle parent)
{
  child->pane.parent = parent;
  dllist_append(&parent->pane.children, pane.siblings, child);
}

static void win_rempane(win_handle child)
{
  dllist_unlink(&child->pane.parent->pane.children, pane.siblings, child);
  child->pane.parent = NULL;
}

/* Create a window abstraction and attach it to an existing window */
win_handle win_attach(wimp_winhandle wh, void *handle)
{
  struct win *ALLOCATE(r);

  task_seterr(NULL);
  if (!r) return NULL;
  r->eh = event_setpre(&win_eventproc, r);
  if (!r->eh) {
    free(r);
    return NULL;
  }
  r->wh = wh;
  r->user.handle = handle;
  r->user.redraw = NULL;
  r->user.update = NULL;
  r->user.click = NULL;
  r->user.key = NULL;
  r->user.open = NULL;
  r->user.close = NULL;
  r->user.scroll = NULL;
  r->user.load = NULL;
  r->user.save = NULL;
  r->user.resv = NULL;
  r->user.filled = NULL;
  r->user.help = NULL;
  r->user.caretin = r->user.caretout = NULL;
  r->user.ptrin = r->user.ptrout = NULL;
  r->user.pane = NULL;
  dllist_init(&r->pane.children);
  r->pane.parent = NULL;
  r->xferfail = false;
  r->saveref = wimp_msgref_NONE;
  event_select((1<<wimp_Redraw_Window_Request) |
               (1<<wimp_Mouse_Click) |
               (1<<wimp_Key_Pressed));
  return r;
}

wimp_winhandle win_detach(win_handle r)
{
  wimp_winhandle wh;
  win_handle ch;

  if (!r) return 0;

  if (r->pane.parent)
    win_rempane(r);
  while ((ch = dllist_first(&r->pane.children)) != NULL)
    win_rempane(ch);
  wh = r->wh;
  event_cancel(r->eh);
  event_deselect((1<<wimp_Redraw_Window_Request) |
                 (1<<wimp_Mouse_Click) |
                 (1<<wimp_Key_Pressed));
  win_conf_open(r, NULL);
  win_conf_close(r, NULL);
  win_conf_ptrin(r, NULL);
  win_conf_ptrout(r, NULL);
  win_conf_caretin(r, NULL);
  win_conf_caretout(r, NULL);
  win_conf_scroll(r, NULL);
  win_conf_load(r, NULL);
  win_conf_save(r, NULL);
  win_conf_ramxfer(r, NULL, NULL);
  win_conf_help(r, NULL);
  free(r);
  return wh;
}

void win_conf_pane(win_handle wh, win_paneproc *pf)
{
  if (!wh) return;
  wh->user.pane = pf;
}

void win_makepane(win_handle child, win_handle parent)
{
  if (!child) return;
  if (child->pane.parent && !parent)
    win_rempane(child);
  else if (!child->pane.parent && parent)
    win_addpane(child, parent);
  else if (child->pane.parent != parent) {
    win_rempane(child);
    win_addpane(child, parent);
  }
}

/* compare a raw window handle with a window abstraction */
int win_matchhandle(win_handle r, wimp_winhandle wh)
{
  return ((r->wh ^ wh) & 0x7fff) == 0;
}

/* Get window attributes */
int win_isopen(win_handle r)
{
  wimp_winstateblock ws;
  ws.wh = r->wh;
  THROW(wimp_getwindowstate(&ws));
  return ws.state.flags.bits.is_open;
}

/* Alter window attributes */
int win_resize(win_handle r, const vdu_box *workarea)
{
  THROW(wimp_setextent(r->wh, workarea));
  return 0;
}

void win_close(win_handle r)
{
  win_handle child;
  for (child = dllist_last(&r->pane.children); child;
       child = dllist_prev(pane.siblings, child))
    win_close(child);

  // We'll just have to assume that this can never fail.
  IGNORE(wimp_closewindow(r->wh));
}

/* Redraw using Wimp_ForceRedraw */
int win_redraw(win_handle r, const vdu_box *ap)
{
  THROW(wimp_forceredraw(r->wh, ap));
  return 0;
}

static int win_gettopwin(win_handle r, wimp_winhandle *whp)
{
  wimp_winstateblock block;
  win_handle child;

  if (!r) STOP;
  block.wh = r->wh;
  THROW(wimp_getwindowstate(&block));
  if (!block.state.flags.bits.is_open)
    return -1;

  child = dllist_last(&r->pane.children);
  while (child && win_gettopwin(child, whp) < 0)
    child = dllist_prev(pane.siblings, child);

  if (!child) *whp = block.state.loc.behind;
  return 0;
}

int win_getstate(win_handle r, wimp_winstate *s)
{
  wimp_winstateblock block;

  block.wh = r->wh;
  THROW(wimp_getwindowstate(&block));
  THROWI(win_gettopwin(dllist_last(&r->pane.children),
                       &block.state.loc.behind));
  *s = block.state;
  return 0;
}

int win_getextent(win_handle r, vdu_box *a)
{
  wimp_wininfoblock block;

  if (!r || !a) STOP;
  block.wh = r->wh;
  THROW(wimp_getwindowinfo_only(&block));
  *a = block.info.workarea;
  return 0;
}

int win_settitle(win_handle r, const char *data)
{
  wimp_wininfoblock block;
  wimp_outlineblock olblock;

  if (!r || !data) STOP;

  block.wh = r->wh;
  THROW(wimp_getwindowinfo_only(&block));
  if (!block.info.title_flags.bits_colour.indirected)
    return -1;
  strncpy(block.info.title_data.indirected_text.buffer, data,
          block.info.title_data.indirected_text.buflen - 1);
  block.info.title_data.indirected_text.buffer
    [block.info.title_data.indirected_text.buflen - 1] = '\0';
  if (block.info.state.flags.bits.is_open) {
    olblock.wh = r->wh;
    THROW(wimp_getwindowoutline(&olblock));
    olblock.box.min.y = block.info.state.loc.dim.visible.max.y;
    return win_redraw(r, &olblock.box);
  }
  return 0;
}

int win_setextent(win_handle w, vdu_box *a)
{
  wimp_wininfoblock block;

  if (!w || !a) STOP;

  /* NEEDED: ensure box specifies a whole number of pixels */

  block.wh = w->wh;
  THROW(wimp_getwindowinfo_only(&block));

  if (block.info.state.flags.bits.is_open) {
    /* Ensure visible area is within new extent. */
    vdu_box visible_work;
    vdu_ord diff;

    /* Get equivalent screen co-ordinates. */
    wimp_work2screen_area(&block.info.state.loc.dim, &visible_work, a);

    /* Ensure window's visible area is still within desired extent. */
    if (block.info.state.loc.dim.visible.min.x < visible_work.min.x)
      block.info.state.loc.dim.visible.min.x = visible_work.min.x;
    if (block.info.state.loc.dim.visible.min.y < visible_work.min.y)
      block.info.state.loc.dim.visible.min.y = visible_work.min.y;
    if (block.info.state.loc.dim.visible.max.x > visible_work.max.x)
      block.info.state.loc.dim.visible.max.x = visible_work.max.x;
    if (block.info.state.loc.dim.visible.max.y > visible_work.max.y)
      block.info.state.loc.dim.visible.max.y = visible_work.max.y;

    /* Check for minimum size: alter extent if necessary. */
    diff = block.info.min_width - block.info.state.loc.dim.visible.max.x
      + block.info.state.loc.dim.visible.min.x;
    if (diff > 0) {
      block.info.state.loc.dim.visible.max.x += diff;
      a->max.x += diff;
    }
    diff = block.info.min_height - block.info.state.loc.dim.visible.max.y
      + block.info.state.loc.dim.visible.min.y;
    if (diff > 0) {
      block.info.state.loc.dim.visible.min.y -= diff;
      a->min.y -= diff;
    }

    /* Re-open the window with the new dimensions. */
    THROW(wimp_openwindow((wimp_openwinreq *) &block));
  }

  /* Now it's safe to set the extent. */
  THROW(wimp_setextent(w->wh, a));

  return 0;
}

wimp_winhandle win_rawhandle(win_handle r) { return r->wh; }

static int win_openat_c(win_handle, wimp_openwinreq *);
static int win_gettopwin(win_handle, wimp_winhandle *);

int win_openat(win_handle r, const wimp_winloc *ap)
{
  wimp_openwinreq req;

  req.wh = r->wh;
  req.loc = *ap;
#if 0
  if (kbd_test(ikn_SHIFT)) {
    vdu_point origin = { 0, 0 };
    text_leavegfx();
    text_setpos(&origin);
    printf("Window %08X opening below %08X\n", r->wh, ap->behind);
    text_joingfx();
    bell_emit();
  }
#endif
  if (r->wh == ap->behind)
    THROWI(win_gettopwin(r, &req.loc.behind));
  return win_openat_c(r, &req);
}

int win_open(win_handle r)
{
  union {
    wimp_winstateblock wsb;
    wimp_openwinreq req;
  } block;

  block.wsb.wh = r->wh;
  THROW(wimp_getwindowstate(&block.wsb));
  win_gettopwin(r, &block.req.loc.behind);
  return win_openat_c(r, &block.req);
#if 0
  wimp_winstateblock ws;
  ws.wh = r->wh;
  THROW(wimp_getwindowstate(&ws));
  return win_openat(r, &ws.state.loc);
#endif
}

static int win_openat_r(win_handle r, wimp_openwinreq *reqp)
{
#if defined(PANEDIR_DOWNWARDS)
  win_handle child;
  union {
    wimp_winstateblock wsb;
    wimp_openwinreq req;
  } block;

  for (child = dllist_last(&r->pane.children); child;
       child = dllist_prev(pane.siblings, child)) {
    block.wsb.wh = child->wh;
    THROW(wimp_getwindowstate(&block.wsb));
    if (child->user.pane &&
      (*child->user.pane)(child->user.handle, &reqp->loc.dim,
                          &block.wsb.state.loc.dim)) {
      block.req.loc.behind = reqp->loc.behind;
      THROWI(win_openat_c(child, &block.req));
      reqp->loc.behind = child->wh;
    } else {
      THROW(wimp_closewindow(child->wh));
    }
  }
#elif defined(PANEDIR_UPWARDS)
  win_handle child;
  union {
    wimp_winstateblock wsb;
    wimp_openwinreq req;
  } block;

  for (child = dllist_first(&r->pane.children); child;
       child = dllist_next(pane.siblings, child)) {
    block.wsb.wh = child->wh;
    THROW(wimp_getwindowstate(&block.wsb));
    if (child->user.pane &&
      (*child->user.pane)(child->user.handle, &reqp->loc.dim,
                          &block.wsb.state.loc.dim)) {
      block.req.loc.behind = reqp->loc.behind;
      THROWI(win_openat_c(child, &block.req));
    } else {
      THROW(wimp_closewindow(child->wh));
    }
  }
#else
#error "Pane-opening direction not defined"
#endif
  return 0;
}

static int win_openat_c(win_handle r, wimp_openwinreq *reqp)
{
#if defined(PANEDIR_DOWNWARDS)
  wimp_winhandle cover = reqp->loc.behind;
  wimp_windim olddim = reqp->loc.dim;

  THROWI(win_openat_r(r, reqp));
  THROW(wimp_openwindow(reqp));
  reqp->loc.behind = cover;
  if (wimp_cmpdims(&reqp->loc.dim, &olddim))
    return win_openat_r(r, reqp);
  return 0;
#elif defined(PANEDIR_UPWARDS)
  THROW(wimp_openwindow(reqp)); /* corrected co-ordinates are written back */
  return win_openat_r(r, reqp); /* open children, recursively */
#else
#error Pane-opening direction not defined
#endif
}
