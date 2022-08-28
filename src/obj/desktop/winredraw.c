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

int win_redrawall(win_handle r)
{
  wimp_winstateblock block;
  vdu_box workarea;

  block.wh = r->wh;
  THROW(wimp_getwindowstate(&block));
  wimp_screen2work_area(&block.state.loc.dim, &workarea,
                        &block.state.loc.dim.visible);
  return win_redraw(r, &workarea);
}

int win_update_usrf(win_handle r, const vdu_box *ap, win_redrawproc *f)
{
  int more;
  wimp_rectangleblock block;

  // TODO: Check whether this should do anything?
  //if (!r->user.update)
  // return 0;

  block.wh = r->wh;
  block.rect.dim.visible = *ap;
  THROW(wimp_updatewindow(&block, &more));
  while (more) {
    wimp_screen2work_area(&block.rect.dim,
                          &block.rect.clip, &block.rect.clip);
    (*f)(r->user.handle, &block.rect.dim, &block.rect.clip);
    THROW(wimp_getrectangle(&block, &more));
  }

  return 0;
}

int win_update(win_handle r, const vdu_box *ap)
{
  return win_update_usrf(r, ap, r->user.update);
}
