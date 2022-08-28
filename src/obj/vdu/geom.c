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

#include "../riscos/vdu/geom.h"

void vdu_canonbox(vdu_box *b, const vdu_box *ri)
{
  vdu_ord tmp;

  if (b != ri)
    *b = *ri;

  if (b->min.x > b->max.x)
    tmp = b->min.x, b->min.x = b->max.x, b->max.x = tmp;
  if (b->min.y > b->max.y)
    tmp = b->min.y, b->min.y = b->max.y, b->max.y = tmp;
}

void vdu_findboxcentre(vdu_point *p, const vdu_box *ri)
{
  p->x = (ri->min.x + ri->max.x) / 2;
  p->y = (ri->min.y + ri->max.y) / 2;
}
