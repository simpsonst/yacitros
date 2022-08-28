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

#include <string.h>

#include "../yacitros/vector/intern.h"
#include "../yacitros/vector/generic.h"

void vector_inithdr(vector_hdr *p, vector_otype t)
{
  p->type = t;
  p->parent = NULL;
  p->bboxval = p->sizeval = p->ftabval = 0;
}

void vector_invalbbox(vector_obj *p)
{
  if (!p || !p->hdr.bboxval)
    return;

  p->hdr.bboxval = 0;
  vector_invalbbox(p->hdr.parent);
}

void vector_invalsize(vector_obj *p)
{
  if (!p || !p->hdr.sizeval)
    return;

  p->hdr.sizeval = 0;
  vector_invalsize(p->hdr.parent);
}

void vector_invalftab(vector_obj *p)
{
  if (!p || !p->hdr.ftabval)
    return;

  p->hdr.ftabval = 0;
  vector_invalftab(p->hdr.parent);
}

void vector_destroy(vector_obj *p)
{
  if (!p)
    return;

  switch (p->hdr.type) {
  case vector_OTEXT:
    vector_destroytext((vector_textobj *) p);
    return;
  case vector_OSPRITE:
    vector_destroysprite((vector_spriteobj *) p);
    return;
  case vector_OTAGGED:
    vector_destroytagged((vector_taggedobj *) p);
    return;
  case vector_OGROUP:
    vector_destroygroup((vector_groupobj *) p);
    return;
  case vector_OFILE:
    vector_destroyfile((vector_fileobj *) p);
    return;
  case vector_OPATH:
    vector_destroypath((vector_pathobj *) p);
    return;
  }
}

int vector_getsize(vector_obj *p, size_t *sp)
{
  if (!p)
    return -1;

  switch (p->hdr.type) {
  case vector_OTEXT:
    return vector_getsizetext((vector_textobj *) p, sp);
  case vector_OSPRITE:
    return vector_getsizesprite((vector_spriteobj *) p, sp);
  case vector_OTAGGED:
    return vector_getsizetagged((vector_taggedobj *) p, sp);
  case vector_OGROUP:
    return vector_getsizegroup((vector_groupobj *) p, sp);
  case vector_OFILE:
    return vector_getsizefile((vector_fileobj *) p, sp);
  case vector_OPATH:
    return vector_getsizepath((vector_pathobj *) p, sp);
  }
  return -1;
}

int vector_write(vector_obj *p, uint8_t **pp, uint8_t *z, vector_fonttab *ft)
{
  if (!p)
    return -1;

  switch (p->hdr.type) {
  case vector_OTEXT:
    return vector_writetext((vector_textobj *) p, pp, z, ft);
  case vector_OSPRITE:
    return vector_writesprite((vector_spriteobj *) p, pp, z, ft);
  case vector_OTAGGED:
    return vector_writetagged((vector_taggedobj *) p, pp, z, ft);
  case vector_OGROUP:
    return vector_writegroup((vector_groupobj *) p, pp, z, ft);
  case vector_OFILE:
    return vector_writefile((vector_fileobj *) p, pp, z, ft);
  case vector_OPATH:
    return vector_writepath((vector_pathobj *) p, pp, z, ft);
  }
  return -1;
}

int vector_print(vector_obj *p, FILE *fp, vector_fonttab *ft)
{
  if (!p)
    return -1;

  switch (p->hdr.type) {
  case vector_OTEXT:
    return vector_printtext((vector_textobj *) p, fp, ft);
  case vector_OSPRITE:
    return vector_printsprite((vector_spriteobj *) p, fp, ft);
  case vector_OTAGGED:
    return vector_printtagged((vector_taggedobj *) p, fp, ft);
  case vector_OGROUP:
    return vector_printgroup((vector_groupobj *) p, fp, ft);
  case vector_OFILE:
    return vector_printfile((vector_fileobj *) p, fp, ft);
  case vector_OPATH:
    return vector_printpath((vector_pathobj *) p, fp, ft);
  }
  return -1;
}

int vector_getbox(vector_obj *p, vector_box *bb, unsigned ow)
{
  if (!p)
    return -1;

  switch (p->hdr.type) {
  case vector_OTEXT:
    return vector_getboxtext((vector_textobj *) p, bb, ow);
  case vector_OSPRITE:
    return vector_getboxsprite((vector_spriteobj *) p, bb, ow);
  case vector_OTAGGED:
    return vector_getboxtagged((vector_taggedobj *) p, bb, ow);
  case vector_OGROUP:
    return vector_getboxgroup((vector_groupobj *) p, bb, ow);
  case vector_OFILE:
    return 0;
  case vector_OPATH:
    return vector_getboxpath((vector_pathobj *) p, bb, ow);
  }
  return -1;
}

int vector_getfonts(vector_obj *p, vector_fonttab *ft)
{
  if (!p)
    return -1;

  switch (p->hdr.type) {
  case vector_OTEXT:
    return vector_getfontstext((vector_textobj *) p, ft);
  case vector_OTAGGED:
    return vector_getfontstagged((vector_taggedobj *) p, ft);
  case vector_OGROUP:
    return vector_getfontsgroup((vector_groupobj *) p, ft);
  case vector_OFILE:
  case vector_OPATH:
  case vector_OSPRITE:
    return 0;
  }
  return -1;
}

int vector_translate(vector_obj *p, vector_ord dx, vector_ord dy)
{
  if (!p) return -1;
  switch (p->hdr.type) {
  case vector_OTEXT:
    return vector_translatetext((vector_textobj *) p, dx, dy);
  case vector_OTAGGED:
    return vector_translatetagged((vector_taggedobj *) p, dx, dy);
  case vector_OGROUP:
    return vector_translategroup((vector_groupobj *) p, dx, dy);
  case vector_OFILE:
    return vector_translatefile((vector_fileobj *) p, dx, dy);
  case vector_OPATH:
    return vector_translatepath((vector_pathobj *) p, dx, dy);
  case vector_OSPRITE:
    return vector_translatesprite((vector_spriteobj *) p, dx, dy);
  default:
    return -1;
  }
}

int vector_align(vector_obj *p, const vector_box *b, unsigned a)
{
  vector_ord dx = 0, dy = 0;
  if (!p) return -1;
  if (vector_getbox(p, NULL, 0) < 0) return -1;
  switch (a & 3) {
  case vector_LEFT:
    dx = b->min.x - p->hdr.bbox.min.x;
    break;
  case vector_CENTRE:
    dx = (b->min.x + b->max.x) / 2.0 -
      (p->hdr.bbox.min.x + p->hdr.bbox.max.x) / 2.0;
    break;
  case vector_RIGHT:
    dx = b->max.x - p->hdr.bbox.max.x;
    break;
  }
  switch (a & 12) {
  case vector_BOTTOM:
    dy = b->min.y - p->hdr.bbox.min.y;
    break;
  case vector_MIDDLE:
    dy = (b->min.y + b->max.y) / 2.0 -
      (p->hdr.bbox.min.y + p->hdr.bbox.max.y) / 2.0;
    break;
  case vector_TOP:
    dy = b->max.y - p->hdr.bbox.max.y;
    break;
  }
#ifdef DEBUG
  fprintf(stderr, "  Shifting by %f %f\n", dx / vector_INCH, dy / vector_INCH);
#else
  vector_translate(p, dx, dy);
#endif
  return 0;
}

void vector_v2dbox(draw_box *d, const vector_box *v)
{
  if (!d || !v) return;
  d->min.x = draw_makeord(v->min.x, draw_UNIT);
  d->min.y = draw_makeord(v->min.y, draw_UNIT);
  d->max.x = draw_makeord(v->max.x, draw_UNIT);
  d->max.y = draw_makeord(v->max.y, draw_UNIT);
}

