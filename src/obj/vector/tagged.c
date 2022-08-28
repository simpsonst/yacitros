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

#include <stdlib.h>

#include "../yacitros/vector/intern.h"
#include "../yacitros/vector/tagged.h"

vector_taggedobj *vector_tagged_create(void);

/* tagged object operations */
int vector_tagged_settag(vector_taggedobj *p, unsigned);
int vector_tagged_insertobj(vector_taggedobj *p, vector_obj *);
int vector_tagged_removeobj(vector_taggedobj *p, vector_obj **);

void vector_destroytagged(vector_taggedobj *p)
{
}

int vector_getsizetagged(vector_taggedobj *p, size_t *sp)
{
  return -1;
}

int vector_writetagged(vector_taggedobj *p,
                       uint8_t **pp, uint8_t *z, vector_fonttab *ft)
{
  return -1;
}

int vector_printtagged(vector_taggedobj *p, FILE *fp, vector_fonttab *ft)
{
  return -1;
}

int vector_getboxtagged(vector_taggedobj *p, vector_box *bb, unsigned ow)
{
  return -1;
}

int vector_getfontstagged(vector_taggedobj *p, vector_fonttab *ft)
{
  return -1;
}

int vector_translatetagged(vector_taggedobj *p,
                           vector_ord dx, vector_ord dy)
{
  return -1;
}

