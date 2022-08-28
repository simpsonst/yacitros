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

#ifndef Yacitros_desktop_dataxfer
#define Yacitros_desktop_dataxfer

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "../../riscos/vdu/types.h"
#include "../../riscos/wimp/types.h"
#include "../../riscos/file/types.h"

#include "../common.h"

  typedef struct {
    wimp_winhandle wh;
    wimp_iconhandle ih;
    vdu_point pos;
    ptrdiff_t size;
    file_type type;
    char name[212];
  } dataxfer_filemsg;
  Yacitros_deprecated(typedef dataxfer_filemsg dataxfer_filemsg_t);

  typedef struct {
    void *buffer;
    size_t len;
  } dataxfer_memmsg;
  Yacitros_deprecated(typedef dataxfer_memmsg dataxfer_memmsg_t);

  typedef struct {
    wimp_msghdr hdr;
    union {
      dataxfer_filemsg file;
      dataxfer_memmsg mem;
    } body;
  } dataxfer_msgblock;
  Yacitros_deprecated(typedef dataxfer_msgblock dataxfer_msgblock_t);

#define dataxfer_SCRAPFILENAME "<Wimp$Scrap>"

  int dataxfer_limmsg(dataxfer_msgblock *b);

#ifdef __cplusplus
}
#endif

#endif
