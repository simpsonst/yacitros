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

#ifndef Yacitros_desktop_template
#define Yacitros_desktop_template

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "../../riscos/wimp/types.h"
#include "../../riscos/font/types.h"
#include "../../riscos/sprite/types.h"

#include "types.h"

  void template_init(const char *s);
  void template_term(void);

  /* size_t template_sizeof(size_t) */
#define template_sizeof(N) \
(sizeof(wimp_wininfo) + (N) * sizeof(wimp_iconstate))

  /* wimp_icon *template_icon(template_handle, size_t) */
#define template_icon(T,N) (wimp_winicons(T->info) + (N))

  /* wimp_wininfo *template_win(template_handle); */
#define template_win(T) (T->info)

  template_handle template_load(const char *, int *pos,
                                size_t icons, size_t space);
  template_handle template_loadwf(const char *,
                                  int *pos, size_t, size_t, font_htab);
  void template_setsprites(template_handle, sprite_area);
  void *template_release(template_handle); /* returns workspace */
  template_handle template_copy(template_handle h);

  struct template {
    wimp_wininfo *info;
    void *ws;
    size_t wslen;
  };

#ifdef __cplusplus
}
#endif

#endif
