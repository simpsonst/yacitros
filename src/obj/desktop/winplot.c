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

int win_plot(const win_offset *d, int pc, const vdu_point *p)
{
  if ((pc & 7) >= 4)
    THROW(vdu_plot(pc, wimp_work2screen_x(d, p->x),
                   wimp_work2screen_y(d, p->y)));
  else
    THROW(vdu_plot(pc, p->x, p->y));
  return 0;
}

int win_plotpoint(const win_offset *d, const vdu_point *p)
{
  return win_plot(d, 69, p);
}

int win_draw(const win_offset *d, const vdu_point *p)
{
  return win_plot(d, 5, p);
}

int win_drawby(const win_offset *d, const vdu_point *p)
{
  return win_plot(d, 1, p);
}

int win_move(const win_offset *d, const vdu_point *p)
{
  return win_plot(d, 4, p);
}

int win_moveby(const win_offset *d, const vdu_point *p)
{
  return win_plot(d, 0, p);
}

int win_fillrectangle(const win_offset *d, const vdu_box *b)
{
  vdu_point extra;
  THROWI(win_plot(d, 4, &b->min));
  extra.x = b->max.x - 1;
  extra.y = b->max.y - 1;
  return win_plot(d, 101, &extra);
}

int win_drawrectangle(const win_offset *d, const vdu_box *b)
{
  vdu_point extra;
  THROWI(win_plot(d, 4, &b->min));
  extra.x = b->min.x;
  extra.y = b->max.y - 1;
  THROWI(win_plot(d, 5, &extra));
  extra.x = b->max.x - 1;
  THROWI(win_plot(d, 5, &extra));
  extra.y = b->min.y;
  THROWI(win_plot(d, 5, &extra));
  return win_plot(d, 5, &b->min);
}

int win_fillcircle(const win_offset *d, const vdu_point *p, vdu_ord r)
{
  THROWI(win_plot(d, 4, p));
  THROW(vdu_plot(153, 0, r));
  return 0;
}

int win_drawcircle(const win_offset *d, const vdu_point *p, vdu_ord r)
{
  THROWI(win_plot(d, 4, p));
  THROW(vdu_plot(145, 0, r));
  return 0;
}
