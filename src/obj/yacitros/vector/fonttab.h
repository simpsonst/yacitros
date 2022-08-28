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

#ifndef Yacitros_vector_fonttab
#define Yacitros_vector_fonttab

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "types.h"

#include "../common.h"

  int vector_getfonttabsize(vector_fonttab *ft, size_t *fp);
  int vector_printfonttab(vector_fonttab *ft, FILE *fp);
  int vector_writefonttab(vector_fonttab *ft, uint8_t **pp, uint8_t *z);
  int vector_createfonttab(vector_fonttab *ft);
  int vector_deletefonttab(vector_fonttab *ft);
  int vector_renumberfonttab(vector_fonttab *ft);
  int vector_addfont(vector_fonttab *ft, const char *n);
  unsigned vector_findfont(vector_fonttab *ft, const char *n);

#ifdef __cplusplus
}
#endif

#endif
