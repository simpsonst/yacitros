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

#ifndef Yacitros_desktop_menu
#define Yacitros_desktop_menu

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>

#include <kernel.h>

#include "../common.h"

#include "../../riscos/vdu/types.h"
#include "../../riscos/wimp/types.h"

#include "types.h"

#define menu_DIALOG ((menu_handle) 0x1000)

  Yacitros_USERESULT
  menu_handle menu_create(const char *title, const char *fmt);
  void menu_destroy(menu_handle);
  void menu_destroytree(menu_handle);
  int menu_attachsubmenu(menu_handle, int ino, menu_handle sub);
  int menu_attachsubwindow(menu_handle, int ino, wimp_winhandle);
#if 0
  int menu_setlength(menu_handle, int ino);
#endif

  int menu_warn(menu_handle, int ino, int);
  int menu_tick(menu_handle, int ino, int);
  int menu_select(menu_handle, int ino, int);
  int menu_dotted(menu_handle, int ino, int);

  /* Allocation of this data is handled by the library. */
  int menu_setdata(menu_handle, int ino, const char *s);

#if 0
  /* Don't use these two anymore. */
  int menu_setdata_static(menu_handle, int ino, const char s[12]);
  int menu_setdata_indirected(menu_handle, int ino, const char *, size_t);
#endif

  /* Allocation of this data remains the responsibility of the
     user. */
  int menu_setdata_writeable(menu_handle, int ino, char *,
                             const char *val, size_t);

  vdu_ord menu_height(menu_handle);

  menu_attachment menu_attach(wimp_winhandle wh, menu_genproc *gen,
                              menu_selproc *ch, menu_warnproc *op,
                              menu_helpproc *help, void *handle);
  void menu_detach(menu_attachment ah);
  void menu_close(void);


  Yacitros_USERESULT
  int menu_open(wimp_winhandle wh, wimp_iconhandle ih,
                const vdu_point *posp,
                menu_genproc *, menu_selproc *, menu_warnproc *,
                menu_helpproc *, void *);

  Yacitros_USERESULT
  int menu_openfromevent(const wimp_mouseevent *, menu_genproc *,
                         menu_selproc *, menu_warnproc *,
                         menu_helpproc *, void *);

  Yacitros_USERESULT
  int menu_opensub(menu_handle, vdu_ord x, vdu_ord y);

  Yacitros_USERESULT
  int menu_openwin(wimp_winhandle wh, vdu_ord x, vdu_ord y);

  Yacitros_USERESULT
  int menu_opensubwin(wimp_winhandle wh, vdu_ord x, vdu_ord y);

#ifdef __cplusplus
}
#endif

#endif
