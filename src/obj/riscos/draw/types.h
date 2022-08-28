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

#ifndef Yacitros_draw_types
#define Yacitros_draw_types

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

#include "../vdu/types.h"

#include "../../yacitros/common.h"

  typedef vdu_ord draw_ord;
  Yacitros_deprecated(typedef draw_ord draw_ord_t);
  typedef vdu_point draw_point;
  Yacitros_deprecated(typedef draw_point draw_point_t);
  typedef vdu_box draw_box;
  Yacitros_deprecated(typedef draw_box draw_box_t);
  typedef vdu_xform draw_xform;
  Yacitros_deprecated(typedef draw_xform draw_xform_t);

#define draw_UNIT (1.0)
#define draw_POINT (640.0)
#define draw_INCH (180.0 * 256.0)
#define draw_XFORM (256.0 * 256.0)
#define draw_MM (draw_INCH / 51.0 * 2.0)
#define draw_MITREQ (256.0 * 256.0)
#define draw_TRISCALE (256.0)

#define draw_makeord(X,U) ((draw_ord) ((double) (X) * (U)))

  typedef uint32_t draw_pelkind;
  Yacitros_deprecated(typedef draw_pelkind draw_pelkind_t);
#define draw_PEND UINT32_C(0)
#define draw_PCONT UINT32_C(1)
#define draw_PMOVE UINT32_C(2)
#define draw_PMOVENWNE UINT32_C(3)
#define draw_PCLOSEGAP UINT32_C(4)
#define draw_PCLOSE UINT32_C(5)
#define draw_PBEZIER UINT32_C(6)
#define draw_PGAP UINT32_C(7)
#define draw_PLINE UINT32_C(8)

  typedef union draw_pel {
    draw_pelkind type;
    struct {
      draw_pelkind type;
      uint32_t n;
    } end;
    struct {
      draw_pelkind type;
      union draw_pel *next;
    } cont;
    struct {
      draw_pelkind type;
      draw_point p;
    } movewne, movenwne, gap, line;
    struct {
      draw_pelkind type;
      draw_point p1, p2, p3;
    } bezier;
    struct {
      draw_pelkind type;
    } closegap, closeline;
  } draw_pel;
  Yacitros_deprecated(typedef draw_pel draw_pel_t);

#define draw_FWINDNZ  0
#define draw_FWINDNEG 1
#define draw_FWINDEO  2
#define draw_FWINDPOS 3

#define draw_FPNBEX 4
#define draw_FPBEX  8
#define draw_FPBIN  16
#define draw_FPNBIN 32

#define draw_FCLOSE 0x08000000
#define draw_FFLAT 0x10000000
#define draw_FTHICK 0x20000000
#define draw_FFLAT2 0x40000000
#define draw_FFP 0x80000000

#define draw_JMITRED 0
#define draw_JROUND 1
#define draw_JBEVELLED 2

#define draw_CBUTT 0
#define draw_CROUND 1
#define draw_CSQUARE 2
#define draw_CTRIANGULAR 3

  typedef struct {
    uint32_t width : 16, height : 16;
  } draw_tridim;
  Yacitros_deprecated(typedef draw_tridim draw_tridim_t);

  typedef struct {
    unsigned join : 8, leadcap : 8, trailcap : 8, padding : 8;
    draw_ord mitre;
    unsigned leadw : 16, leadh : 16;
    unsigned trailw : 16, trailh : 16;
  } draw_capjoin;
  Yacitros_deprecated(typedef draw_capjoin draw_capjoin_t);

  typedef struct {
    draw_ord start;
    uint32_t length;
    draw_ord elem[1];
  } draw_dashpat;
  Yacitros_deprecated(typedef draw_dashpat draw_dashpat_t);

#define draw_sizeofdashpat(N) (sizeof(draw_dashpat) + \
                               (N - 1) * sizeof(draw_ord))
  typedef union {
    uint32_t word;
    struct {
      unsigned join : 2, endcap : 2, startcap : 2, wind : 1, dash : 1;
      unsigned pad0 : 8, triwidth : 8, trihgt : 8;
    } bits;
  } draw_pathstyle;
  Yacitros_deprecated(typedef draw_pathstyle draw_pathstyle_t);

#ifdef __cplusplus
}
#endif

#endif
