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

#include <string.h>

#include "../riscos/wimp/types.h"
#include "../riscos/wimp/win.h"

#include "../yacitros/desktop/iconbar.h"
#include "../yacitros/desktop/win.h"

win_handle iconbar = NULL;

int iconbar_init(void *h)
{
  if (!iconbar) {
    iconbar = win_attach(wimp_WICONBAR, h);
    return 0;
  }
  return -1;
}

void iconbar_term(void)
{
  if (iconbar) win_detach(iconbar), iconbar = NULL;
}

wimp_iconhandle iconbar_appicon(const char *sname, sprite_area sa)
{
  wimp_iconhandle ih;
  wimp_iconstate ib;

  ib.bounds.min.x = 0;
  ib.bounds.min.y = 0;
  ib.bounds.max.x = 68;
  ib.bounds.max.y = 68;

  ib.flags.word = 0x1700311a; /* 00010111 00000000 00110001 00011010 */

  ib.data.indirected_sprite.id.name = (char *) sname;
  ib.data.indirected_sprite.spritearea = sa;
  ib.data.indirected_sprite.length = strlen(sname) + 1;

  if (win_createicon(iconbar, &ib, &ih) < 0)
    return -1;
  return ih;
}
