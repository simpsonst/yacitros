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

#ifndef Yacitros_desktop_types
#define Yacitros_desktop_types

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>
#include <stdint.h>

#include <kernel.h>

#include "../../riscos/file/types.h"
#include "../../riscos/vdu/types.h"
#include "../../riscos/wimp/types.h"
#include "../../riscos/mouse/types.h"

#include "../common.h"

  /* an abstract window handle */
  typedef struct win *win_handle;
  Yacitros_deprecated(typedef win_handle win_t);
  typedef wimp_windim win_offset;
  Yacitros_deprecated(typedef win_offset win_offset_t);

  typedef struct {
#ifdef Yacitros_desktop_msgtranslabel
    uint32_t word[4];
#else
    struct label_node *root;
#endif
  } label_bundle;
  Yacitros_deprecated(typedef label_bundle label_t);

  typedef struct {
    struct {
      vdu_box area;
      vdu_sfact scale;
    } graphics, text;
  } mode_geom;
  Yacitros_deprecated(typedef mode_geom mode_geom_t);

  typedef struct {
    mode_geom geom;
    int modeno;
    _kernel_oserror err;
  } wimpmode_state;
  Yacitros_deprecated(typedef wimpmode_state wimpmode_state_t);

  typedef struct template *template_handle;
  Yacitros_deprecated(typedef template_handle template_t);

  typedef wimp_menuhdr *menu_handle;
  Yacitros_deprecated(typedef menu_handle menu_t);
  typedef struct menu_attachmentstr *menu_attachment;
  Yacitros_deprecated(typedef menu_attachment menu_attachment_t);

  /* Event responsibilty */
  typedef enum {
    event_CLAIM = 0,
    event_SHIRK = 1
  } event_rspcode;
  Yacitros_deprecated(typedef event_rspcode event_rsp_t);

  typedef struct event_procstr *event_ref;
  Yacitros_deprecated(typedef event_ref event_t);
  typedef struct event_idler *event_idlerref;
  Yacitros_deprecated(typedef event_idlerref event_idler_t);

  typedef void drag_proc(void *, const vdu_box *);
  Yacitros_deprecated(typedef drag_proc drag_proc_t);

  typedef void menu_selproc(void *, const wimp_menuchoice *);
  Yacitros_deprecated(typedef menu_selproc menu_sel_proc_t);
  typedef void menu_warnproc(void *, const wimp_menuchoice *,
                             const vdu_point *pos);
  Yacitros_deprecated(typedef menu_warnproc menu_op_proc_t);
  typedef menu_handle menu_genproc(void *, wimp_winhandle, wimp_iconhandle,
                                   vdu_point *);
  Yacitros_deprecated(typedef menu_genproc menu_gen_proc_t);
  typedef const char *menu_helpproc(void *, const wimp_menuchoice *);
  Yacitros_deprecated(typedef menu_helpproc menu_help_proc_t);

  typedef void *transmit_supplyproc(void *, size_t *);
  Yacitros_deprecated(typedef transmit_supplyproc transmit_supply_proc_t);
  typedef int transmit_depositproc(void *, const char *, int safe);
  Yacitros_deprecated(typedef transmit_depositproc transmit_deposit_proc_t);

  typedef struct {
    wimp_msgref lastref;
    event_ref eh;

    void *ctxt;
    transmit_supplyproc *supply;
    transmit_depositproc *deposit;
  } transmit_record;
  Yacitros_deprecated(typedef transmit_record transmit_file_t);

  /* Event handlers */
  typedef event_rspcode event_proc(void *handle,
                                   wimp_eventtype, void *data);
  Yacitros_deprecated(typedef event_proc event_proc_t);

  /* Idlers for null events */
  typedef void event_idlerproc(void *);
  Yacitros_deprecated(typedef event_idlerproc event_idler_proc_t);

  /* file transfer protocol */
  typedef int win_loadproc(void *handle, wimp_iconhandle, const vdu_point *,
                           long, file_type, const char *);
  Yacitros_deprecated(typedef win_loadproc win_load_proc_t);
  typedef int win_saveproc(void *handle, wimp_iconhandle, const vdu_point *,
                           long, file_type, char *, int len);
  Yacitros_deprecated(typedef win_saveproc win_save_proc_t);
  typedef void *win_resvproc(void *, size_t *);
  Yacitros_deprecated(typedef win_resvproc win_resv_proc_t);
  /* resv(ctxt, NULL) => failure */
  typedef void win_filledproc(void *, size_t);
  Yacitros_deprecated(typedef win_filledproc win_filled_proc_t);

  /* interactive help protocol */
  typedef const char *win_helpproc(void *,
                                   const mouse_state *, wimp_iconhandle);
  Yacitros_deprecated(typedef win_helpproc win_help_proc_t);

  /* menu management */
  typedef menu_handle win_menugenproc(void *, wimp_iconhandle, vdu_point *);
  Yacitros_deprecated(typedef win_menugenproc win_menugen_proc_t);
  typedef menu_selproc win_menuselproc;
  Yacitros_deprecated(typedef win_menuselproc win_menusel_proc_t);
  typedef menu_warnproc win_menuwarnproc;
  Yacitros_deprecated(typedef win_menuwarnproc win_menuop_proc_t);
  typedef menu_helpproc win_menuhelpproc;
  Yacitros_deprecated(typedef win_menuhelpproc win_menuhelp_proc_t);
  typedef struct win_menuatstr *win_menuat;
  Yacitros_deprecated(typedef win_menuat win_menuat_t);

  typedef void win_redrawproc(void *handle,
                              const win_offset *,
                              const vdu_box *);
  Yacitros_deprecated(typedef win_redrawproc win_redraw_proc_t);
  typedef event_rspcode win_clickproc(void *handle,
                                      const mouse_state *,
                                      wimp_iconhandle);
  Yacitros_deprecated(typedef win_clickproc win_click_proc_t);
  typedef event_rspcode win_keyproc(void *handle, const wimp_caretpos *,
                                    wimp_iconhandle, wimp_keycode);
  Yacitros_deprecated(typedef win_keyproc win_key_proc_t);
  typedef event_rspcode win_openproc(void *handle, const wimp_winloc *);
  Yacitros_deprecated(typedef win_openproc win_open_proc_t);
  typedef event_rspcode win_closeproc(void *handle);
  Yacitros_deprecated(typedef win_closeproc win_close_proc_t);
  typedef event_rspcode win_scrollproc(void *handle, const wimp_winloc *,
                                       const vdu_point *);
  Yacitros_deprecated(typedef win_scrollproc win_scroll_proc_t);
  typedef event_rspcode win_caretmvproc(void *handle,
                                        const wimp_caretpos *,
                                        wimp_iconhandle);
  Yacitros_deprecated(typedef win_caretmvproc win_caretmv_proc_t);
  typedef event_rspcode win_ptrmvproc(void *handle);
  Yacitros_deprecated(typedef win_ptrmvproc win_ptrmv_proc_t);
  typedef int win_paneproc(void *,
                           const wimp_windim *parent,
                           wimp_windim *cur);
  Yacitros_deprecated(typedef win_paneproc win_pane_proc_t);

#ifdef __cplusplus
}
#endif

#endif
