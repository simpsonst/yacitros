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

#ifndef Yacitros_desktop_win
#define Yacitros_desktop_win

#ifdef __cplusplus
extern "C" {
#endif

#include "../../riscos/vdu/types.h"
#include "../../riscos/mouse/types.h"
#include "../../riscos/wimp/types.h"

#include "types.h"
#include "menu.h"
#include "drag.h"

#include "../common.h"

  /* Create a window from a template */
  win_handle win_create(template_handle, void *);
  void win_destroy(win_handle);

  /* Create a window abstraction and attach it to an existing window */
  win_handle win_attach(wimp_winhandle, void *);
  wimp_winhandle win_detach(win_handle);

  /* compare a raw window handle with a window abstraction */
  int win_matchhandle(win_handle, wimp_winhandle);
  wimp_winhandle win_rawhandle(win_handle); /* should not be needed */

  /* Configure a window abstraction */
  void win_setcontext(win_handle, void *);
  void win_conf_redraw(win_handle, win_redrawproc *);
  void win_conf_update(win_handle, win_redrawproc *);
  void win_conf_click(win_handle, win_clickproc *);
  void win_conf_key(win_handle, win_keyproc *);
  void win_conf_open(win_handle, win_openproc *);
  void win_conf_close(win_handle, win_closeproc *);
  void win_conf_scroll(win_handle, win_scrollproc *);
  void win_conf_caretin(win_handle, win_caretmvproc *);
  void win_conf_caretout(win_handle, win_caretmvproc *);
  void win_conf_ptrin(win_handle, win_ptrmvproc *);
  void win_conf_ptrout(win_handle, win_ptrmvproc *);
  void win_conf_load(win_handle, win_loadproc *);
  void win_conf_save(win_handle, win_saveproc *);
  void win_conf_ramxfer(win_handle, win_resvproc *, win_filledproc *);
  void win_conf_help(win_handle, win_helpproc *);
  void win_conf_pane(win_handle, win_paneproc *);

  /* Pane functions */
  void win_makepane(win_handle pane, win_handle parent);

  /* Get window attributes */
  int win_isopen(win_handle);
  int win_getoutline(win_handle, vdu_box *area);

  /* Alter window attributes */
  Yacitros_USERESULT
  int win_resize(win_handle, const vdu_box *workarea);
  Yacitros_USERESULT
  int win_open(win_handle);
  Yacitros_USERESULT
  int win_openmenu(win_handle, vdu_ord x, vdu_ord y);
  Yacitros_USERESULT
  int win_opensubmenu(win_handle, vdu_ord x, vdu_ord y);
  Yacitros_USERESULT
  int win_openat(win_handle, const wimp_winloc *);
  void win_close(win_handle);

  /* Redraw using Wimp_ForceRedraw */
  Yacitros_USERESULT
  int win_redraw(win_handle, const vdu_box *);
  Yacitros_USERESULT
  int win_redrawall(win_handle);
  Yacitros_USERESULT
  int win_getstate(win_handle, wimp_winstate *);

  /* Redraw immediately */
  Yacitros_USERESULT
  int win_update(win_handle, const vdu_box *);
  Yacitros_USERESULT
  int win_update_usrf(win_handle r,
                      const vdu_box *ap, win_redrawproc *f);

  /* pixel-alignment- and work-area-safe */
  int win_setextent(win_handle, vdu_box *);
  int win_getextent(win_handle, vdu_box *);

  /* icon management */
  int win_createicon(win_handle w,
                     const wimp_iconstate *id, wimp_iconhandle *ip);
  int win_resizeicon(win_handle w, wimp_iconhandle,
                     const vdu_box *, wimp_iconhandle *);
  int win_geticonstate(win_handle w, wimp_iconhandle i, wimp_iconstate *id);
  int win_deleteicon(win_handle w, wimp_iconhandle i);
  int win_seticonflags(win_handle w, wimp_iconhandle i,
                       wimp_iconflags eor, wimp_iconflags clear);
  int win_selecticon(win_handle w, wimp_iconhandle i, int);
  int win_enableicon(win_handle w, wimp_iconhandle i, int);
  int win_iconselected(win_handle, wimp_iconhandle i, int *s);
  int win_iconenabled(win_handle, wimp_iconhandle i, int *s);
  int win_geticonflags(win_handle w, wimp_iconhandle i, wimp_iconflags *fl);
  int win_whichicon(win_handle w, wimp_iconhandle *is,
                    wimp_iconflags mask, wimp_iconflags test);
  int win_dragiconpos(win_handle h,
                      drag_proc *f, void *d, wimp_iconhandle ih);
  int win_setfield(win_handle r, wimp_iconhandle ih, const char *data);
  int win_setfieldn(win_handle r, wimp_iconhandle ih,
                    const char *data, size_t n);
  int win_getfield(win_handle r, wimp_iconhandle ih, char *data, int len);
  int win_setfield_int(win_handle r, wimp_iconhandle ih, int val);
  int win_getfield_int(win_handle r, wimp_iconhandle ih, int *val);
  int win_setval(win_handle r, wimp_iconhandle ih, const char *s);
  int win_settitle(win_handle r, const char *data);

  Yacitros_USERESULT
  win_menuat win_attachmenu(win_handle, win_menugenproc *gen,
                            win_menuselproc *sel, win_menuwarnproc *op,
                            win_menuhelpproc *help, void *handle);
  Yacitros_USERESULT
  int win_openiconmenu(win_handle, wimp_iconhandle,
                       const vdu_point *,
                       win_menugenproc *gen,
                       win_menuselproc *sel,
                       win_menuwarnproc *op,
                       win_menuhelpproc *help,
                       void *handle);
  void win_detachmenu(win_menuat);

  int win_plot(const win_offset *, int, const vdu_point *);
  int win_plotpoint(const win_offset *, const vdu_point *);
  int win_draw(const win_offset *, const vdu_point *);
  int win_drawby(const win_offset *, const vdu_point *);
  int win_move(const win_offset *, const vdu_point *);
  int win_moveby(const win_offset *, const vdu_point *);
  int win_fillrectangle(const win_offset *, const vdu_box *);
  int win_drawrectangle(const win_offset *, const vdu_box *);
  int win_fillcircle(const win_offset *, const vdu_point *, vdu_ord);
  int win_drawcircle(const win_offset *, const vdu_point *, vdu_ord);

#ifdef __cplusplus
}
#endif

#endif
