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

#ifndef Yacitros_vdu_types
#define Yacitros_vdu_types

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "../types.h"

#include "../../yacitros/common.h"

  typedef int32_t vdu_ord;
  Yacitros_deprecated(typedef vdu_ord vdu_ord_t);

  typedef struct {
    vdu_ord x, y;
  } vdu_point;
  Yacitros_deprecated(typedef vdu_point vdu_point_t);

  typedef struct {
    vdu_point min, max;
  } vdu_box;
  Yacitros_deprecated(typedef vdu_box vdu_box_t);

  typedef struct {
    vdu_ord a, b, c, d, e, f;
  } vdu_xform;
  Yacitros_deprecated(typedef vdu_xform vdu_xform_t);

  typedef struct {
    int32_t xmul, ymul, xdiv, ydiv;
  } vdu_sfact;
  Yacitros_deprecated(typedef vdu_sfact vdu_sfact_t);

  typedef uint32_t vdu_varval;
  Yacitros_deprecated(typedef vdu_varval vdu_varval_t);
  typedef int32_t vdu_varno;
  Yacitros_deprecated(typedef vdu_varno vdu_varno_t);

  typedef struct {
    vdu_varno index;
    vdu_varval value;
  } vdu_modepair;
  Yacitros_deprecated(typedef vdu_modepair vdu_modepair_t);

  typedef uint8_t vdu_action, vdu_ground;
  Yacitros_deprecated(typedef vdu_action vdu_action_t);
  Yacitros_deprecated(typedef vdu_ground vdu_ground_t);

#define vdu_FOREGROUND ((vdu_ground) 0x00)
#define vdu_BACKGROUND ((vdu_ground) 0x80)

  typedef uint32_t vdu_palentry;
  Yacitros_deprecated(typedef vdu_palentry vdu_palentry_t);
#define vdu_PALENTRY(R,G,B) \
  ((vdu_palentry) ((((unsigned char) (R) & 0xffu) << 8u) | \
                   (((unsigned char) (G) & 0xffu) << 16u) | \
                   (((unsigned char) (B) & 0xffu) << 24u)))
#define vdu_PALENTRYF(R,G,B) vdu_PALENTRY((R)*255u,(G)*255u,(B)*255u)
#define vdu_GETRED(X) (((X)>>8u)&0xffu)
#define vdu_GETGREEN(X) (((X)>>16u)&0xffu)
#define vdu_GETBLUE(X) (((X)>>24u)&0xffu)

  typedef union {
    uint8_t byte;
    struct {
      unsigned tint : 2, red : 2, green : 2, blue : 2;
    } fields;
  } vdu_gcol;
  Yacitros_deprecated(typedef vdu_gcol vdu_gcol_t);

  typedef uint8_t vdu_colnum;
  Yacitros_deprecated(typedef vdu_colnum vdu_colnum_t);

  typedef struct {
    unsigned one : 1, spec : 6, resv : 24;
    vdu_ord xres, yres;
    uint32_t colexp;
    int32_t frate;
  } vdu_modespec;
  Yacitros_deprecated(typedef vdu_modespec vdu_modespec_t);

#define vdu_modepair(S) ((vdu_modepair *) (1 + (vdu_modespec *) (S)))

  typedef union {
    int32_t number;
    vdu_modespec *spec;
  } vdu_modeid;
  Yacitros_deprecated(typedef vdu_modeid vdu_modeid_t);

#ifdef __cplusplus
}
#endif

#endif
