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

#ifndef Yacitros_vdu_geom
#define Yacitros_vdu_geom

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#if false
  void vdu_addpoints(vdu_point *, const vdu_point *, const vdu_point *);
  void vdu_subpoints(vdu_point *, const vdu_point *, const vdu_point *);
  void vdu_invpoint(vdu_point *, const vdu_point *);
  int vdu_cmppoints(const vdu_point *, const vdu_point *);
  int vdu_cmpboxes(const vdu_box *, const vdu_box *);
  vdu_ord vdu_min(vdu_ord_t, vdu_ord_t);
  vdu_ord vdu_max(vdu_ord_t, vdu_ord_t);
  void vdu_maxbox(vdu_box *, const vdu_box *, const vdu_box *);
  void vdu_minbox(vdu_box *, const vdu_box *, const vdu_box *);
  void vdu_movebox(vdu_box *, const vdu_box *, const vdu_point *);
#endif

  void vdu_canonbox(vdu_box *, const vdu_box *);
  void vdu_findboxcentre(vdu_point *, const vdu_box *);

#define vdu_cmppoints(L,R) ((L)->x != (R)->x || (L)->y != (R)->y)
#define vdu_cmpboxes(L,R) (vdu_cmppoints(&(L)->min, &(R)->min) || \
                            vdu_cmppoints(&(L)->max, &(R)->max))

#define vdu_addpoints(O,L,R) ((void) ((O)->x = (L)->x + (R)->x, \
                                       (O)->y = (L)->y + (R)->y))
#define vdu_subpoints(O,L,R) ((void) ((O)->x = (L)->x - (R)->x, \
                                       (O)->y = (L)->y - (R)->y))
#define vdu_invpoints(O,R) ((void) ((O)->x = -(R)->x, (O)->y = -(R)->y))

#define vdu_min(L,R) ((L)<(R)?(L):(R))
#define vdu_max(L,R) ((L)>(R)?(L):(R))

#define vdu_maxbox(O,L,R) \
((void) ((O)->min.x = vdu_min((L)->min.x, (R)->min.x), \
         (O)->min.y = vdu_min((L)->min.y, (R)->min.y), \
         (O)->max.x = vdu_max((L)->max.x, (R)->max.x), \
         (O)->max.y = vdu_max((L)->max.y, (R)->max.y)))

#define vdu_minbox(O,L,R) \
((void) ((O)->min.x = vdu_max((L)->min.x, (R)->min.x), \
         (O)->min.y = vdu_max((L)->min.y, (R)->min.y), \
         (O)->max.x = vdu_min((L)->max.x, (R)->max.x), \
         (O)->max.y = vdu_min((L)->max.y, (R)->max.y)))

#define vdu_movebox(O,L,R) (vdu_addpoints(&(O)->min, &(L)->min, (R)), \
                            vdu_addpoints(&(O)->max, &(L)->max, (R)))

#ifdef __cplusplus
}
#endif

#endif
