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

#ifndef Yacitros_wimp_op
#define Yacitros_wimp_op

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

#include "../types.h"
#include "../vdu/types.h"
#include "../sprite/args.h"
#include "opblocks.h"

#include "../../yacitros/common.h"

  Yacitros_USERESULT
  _kernel_oserror *wimp_initialise(double version, const char *taskname,
                                   wimp_taskhandle *th,
                                   const wimp_msgtype *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_createwindow(const wimp_wininfo *, wimp_winhandle *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_createicon(const wimp_createiconblock *,
                                   wimp_iconhandle *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_deletewindow(wimp_winhandle);
  Yacitros_USERESULT
  _kernel_oserror *wimp_deleteicon(wimp_winhandle, wimp_iconhandle);
  Yacitros_USERESULT
  _kernel_oserror *wimp_openwindow(const wimp_openwinreq *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_closewindow(wimp_winhandle);
  Yacitros_USERESULT
  _kernel_oserror *wimp_poll(wimp_eventmask,
                             void *data, wimp_eventtype *rc);
  Yacitros_USERESULT
  _kernel_oserror *wimp_redrawwindow(wimp_rectangleblock *, int *more);
  Yacitros_USERESULT
  _kernel_oserror *wimp_updatewindow(wimp_rectangleblock *, int *more);
  Yacitros_USERESULT
  _kernel_oserror *wimp_getrectangle(wimp_rectangleblock *, int *more);
  Yacitros_USERESULT
  _kernel_oserror *wimp_getwindowstate(wimp_winstateblock *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_getwindowinfo(wimp_wininfoblock *);
#if false
#ifdef __GNUC__
#warning "26-bit API used"
#endif
#endif
#define wimp_getwindowinfo_only(B) \
  (wimp_getwindowinfo((wimp_wininfoblock *) (1|(uint32_t) (B))))

  Yacitros_USERESULT
  _kernel_oserror *wimp_seticonstate(wimp_winhandle, wimp_iconhandle,
                                     wimp_iconflags eor,
                                     wimp_iconflags clear);
  Yacitros_USERESULT
  _kernel_oserror *wimp_geticonstate(wimp_iconstateblock *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_getpointerinfo(wimp_mouseevent *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_dragbox(const wimp_dragspec *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_forceredraw(wimp_winhandle wh,
                                    const vdu_box *ap);
  Yacitros_USERESULT
  _kernel_oserror *wimp_setcaretposition(wimp_winhandle wh,
                                         wimp_iconhandle ih,
                                         const wimp_caretpos *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_getcaretposition(wimp_winhandle *wh,
                                         wimp_iconhandle *ih,
                                         wimp_caretpos *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_createmenu(const wimp_menuhdr *,
                                   vdu_ord x, vdu_ord y);
  Yacitros_USERESULT
  _kernel_oserror *wimp_closemenu(void);
  Yacitros_USERESULT
  _kernel_oserror *wimp_createmenuwindow(wimp_winhandle,
                                         vdu_ord x, vdu_ord y);
  Yacitros_USERESULT
  _kernel_oserror *wimp_decodemenu(const wimp_menuhdr *,
                                   const wimp_menuchoice *,
                                   char *answer);
  Yacitros_USERESULT
  _kernel_oserror *wimp_whichicon(wimp_winhandle, wimp_iconhandle *,
                                  wimp_iconflags mask,
                                  wimp_iconflags match);
  Yacitros_USERESULT
  _kernel_oserror *wimp_setextent(wimp_winhandle, const vdu_box *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_setpointershape(int shape_no, uint8_t *data,
                                        int width, int height, int ax, int ay);
  Yacitros_USERESULT
  _kernel_oserror *wimp_opentemplate(const char *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_closetemplate(void);
  Yacitros_USERESULT
  _kernel_oserror *wimp_loadtemplate(wimp_wininfo *, void *ws, size_t len,
                                     font_htab, char name[12], int *pos,
                                     size_t *used);
  Yacitros_USERESULT
  _kernel_oserror *wimp_processkey(wimp_keycode);
  Yacitros_USERESULT
  _kernel_oserror *wimp_closedown(wimp_taskhandle);
  Yacitros_USERESULT
  _kernel_oserror *wimp_starttask(const char *);
  wimp_errrsp wimp_reporterror(const _kernel_oserror *,
                               wimp_errflags, const char *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_getwindowoutline(wimp_outlineblock *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_pollidle(wimp_eventmask, void *data,
                                 wimp_eventtype *rc,
                                 os_monotime earliest);
  Yacitros_USERESULT
  _kernel_oserror *wimp_ploticon(const wimp_iconstate *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_setmode(int);
  Yacitros_USERESULT
  _kernel_oserror *wimp_setpalette(const vdu_palentry pal[20]);
  Yacitros_USERESULT
  _kernel_oserror *wimp_readpalette(vdu_palentry pal[20]);
  Yacitros_USERESULT
  _kernel_oserror *wimp_setcolour(wimp_gcol);
  Yacitros_USERESULT
  _kernel_oserror *wimp_sendmessage_totask(wimp_eventtype,
                                           void *, wimp_taskhandle);
  Yacitros_USERESULT
  _kernel_oserror *wimp_sendmessage_towindow(wimp_eventtype,
                                             void *, wimp_winhandle,
                                             wimp_iconhandle,
                                             wimp_taskhandle *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_sendmessage_broadcast(wimp_eventtype, void *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_createsubmenu(const wimp_menuhdr *,
                                      vdu_ord x, vdu_ord y);
  Yacitros_USERESULT
  _kernel_oserror *wimp_createsubmenuwindow(wimp_winhandle,
                                            vdu_ord x, vdu_ord y);
  Yacitros_USERESULT
  _kernel_oserror *wimp_spriteop(int, const sprite_args *, sprite_args *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_baseofsprites(sprite_area *rom, sprite_area *ram);
  Yacitros_USERESULT
  _kernel_oserror *wimp_blockcopy(wimp_winhandle, const vdu_box *area,
                                  const vdu_point *bl);
  Yacitros_USERESULT
  _kernel_oserror *wimp_slotsize(long *current, long *next, long *pool);
  /* do later: _kernel_oserror *wimp_readpixtrans(); */
  /* do later: _kernel_oserror *wimp_claimfreememory(); */
  Yacitros_USERESULT
  _kernel_oserror *wimp_preparecommandwindow(const char *title);
  Yacitros_USERESULT
  _kernel_oserror *wimp_endcommandwindow(void);
  Yacitros_USERESULT
  _kernel_oserror *wimp_abortcommandwindow(void);

  Yacitros_USERESULT
  _kernel_oserror *wimp_textcolour(wimp_gcol);
  Yacitros_USERESULT
  _kernel_oserror *wimp_transferblock(wimp_taskhandle srct, void *srcb,
                                      wimp_taskhandle dest, void *desb,
                                      size_t);
  Yacitros_USERESULT
  _kernel_oserror *wimp_readsysinfo(long *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_getmenustate(wimp_winhandle, wimp_iconhandle,
                                     wimp_menuchoice *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_setfontcolours(wimp_gcol fg, wimp_gcol bg);
  Yacitros_USERESULT
  _kernel_oserror *wimp_addmessages(const wimp_msgtype *);
  Yacitros_USERESULT
  _kernel_oserror *wimp_removemessages(const wimp_msgtype *);

  /* coordinate translation */
#if false
  void wimp_screen2work(const wimp_windim *dim, vdu_point *work,
                        const vdu_point *screen);
  void wimp_work2screen(const wimp_windim *dim, vdu_point *screen,
                        const vdu_point *work);
#endif

#define wimp_screen2work_x(D,S) ((S) - ((D)->visible.min.x - (D)->scroll.x))
#define wimp_screen2work_y(D,S) ((S) - ((D)->visible.max.y - (D)->scroll.y))
#define wimp_work2screen_x(D,W) ((W) + ((D)->visible.min.x - (D)->scroll.x))
#define wimp_work2screen_y(D,W) ((W) + ((D)->visible.max.y - (D)->scroll.y))

#define wimp_screen2work(D,W,S) \
((W)->x = wimp_screen2work_x(D,(S)->x), (W)->y = wimp_screen2work_y(D,(S)->y))
#define wimp_work2screen(D,S,W) \
((S)->x = wimp_work2screen_x(D,(W)->x), (S)->y = wimp_work2screen_y(D,(W)->y))

#define wimp_screen2work_area(D,W,S) \
(wimp_screen2work((D), &(W)->min, &(S)->min), \
 wimp_screen2work((D), &(W)->max, &(S)->max))
#define wimp_work2screen_area(D,S,W) \
(wimp_work2screen((D), &(S)->min, &(W)->min), \
 wimp_work2screen((D), &(S)->max, &(W)->max))

#define wimp_cmpdims(L,R) (vdu_cmpboxes(&(L)->visible, &(R)->visible) || \
                           vdu_cmppoints(&(L)->scroll, &(R)->scroll))

#define wimp_makegcol(C,A,G) ((wimp_gcol) ((C) & 0xf) | \
                              (((A) & 0x7) << 4) | \
                              ((!!(G) & 1) << 7))

#ifdef __cplusplus
}
#endif

#endif
