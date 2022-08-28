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

#ifndef Yacitros_wimp_opblocks
#define Yacitros_wimp_opblocks

#ifdef __cplusplus
extern "C" {
#endif

#include "../vdu/types.h"
#include "types.h"

#include "../../yacitros/common.h"

  /* Wimp SWI blocks */

  typedef struct {
    wimp_winhandle wh;
    wimp_rectangle rect;
  } wimp_rectangleblock;
  Yacitros_deprecated(typedef wimp_rectangleblock wimp_rectangleblock_t);

  typedef struct {
    wimp_winhandle wh;
    wimp_winstate state;
  } wimp_winstateblock;
  Yacitros_deprecated(typedef wimp_winstateblock wimp_winstateblock_t);

  typedef struct {
    wimp_winhandle wh;
    wimp_wininfo info;
  } wimp_wininfoblock;
  Yacitros_deprecated(typedef wimp_wininfoblock wimp_wininfoblock_t);

  typedef struct {
    wimp_winhandle wh;
    vdu_box box;
  } wimp_outlineblock;
  Yacitros_deprecated(typedef wimp_outlineblock wimp_outlineblock_t);

  typedef struct {
    wimp_winhandle wh;
    wimp_iconstate i;
  } wimp_createiconblock;
  Yacitros_deprecated(typedef wimp_createiconblock wimp_createiconblock_t);

  typedef struct {
    wimp_winhandle wh;
    wimp_iconhandle ih;
    wimp_iconstate i;
  } wimp_iconstateblock;
  Yacitros_deprecated(typedef wimp_iconstateblock wimp_iconstateblock_t);

#ifdef __cplusplus
}
#endif

#endif
