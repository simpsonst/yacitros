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

#include "../riscos/font/op.h"

#include "../yacitros/vector/intern.h"
#include "../yacitros/vector/generic.h"
#include "../yacitros/vector/text.h"
#include "../yacitros/vector/fonttab.h"
#include "../yacitros/vector/link.h"

#include "../utils.h"

vector_textobj *vector_text_create(void)
{
  vector_textobj *ALLOCATE(r);
  if (!r) return NULL;
  vector_inithdr(&r->hdr, vector_OTEXT);
  r->font = r->text = NULL;
  r->width = r->height = vector_makeord(12, vector_POINT);
  r->fore = 0;
  r->back = 0xffffff00;
  return r;
}

static int vector_calctextbbox(vector_textobj *p)
{
  font_dim dim;
  font_handle h;
  vdu_box cbox, sbox;
  if (!p || !p->text) return -1;

  /* set base to 0, 0 */
  p->pos.x = p->pos.y = 0;
  dim.size.x = p->width / vector_POINT * 16.0;
  dim.size.y = p->height / vector_POINT * 16.0;
  dim.res.x = dim.res.y = 0;

  /* open a font */
  if (!p->font || font_find(&h, p->font, &dim, NULL)) {
    cbox.min.y = 0;
    cbox.max.y = p->height;
    sbox.min.x = 0;
    sbox.max.y = p->width * strlen(p->text);
  } else {
    if (font_bbox(h, &cbox)) return -1;
    if (font_os2mp(&cbox.min, &cbox.min)) return -1;
    if (font_os2mp(&cbox.max, &cbox.max)) return -1;
    if (font_c_stringbbox(p->text, &sbox)) return -1;
    if (font_lose(h)) return -1;
  }
  /* now generate a bbox from sbox.x, cbox.y */
  p->hdr.bbox.min.x = vector_makeord(sbox.min.x, vector_MILLIPOINT);
  p->hdr.bbox.min.y = vector_makeord(cbox.min.y, vector_MILLIPOINT);
  p->hdr.bbox.max.x = vector_makeord(sbox.max.x, vector_MILLIPOINT);
  p->hdr.bbox.max.y = vector_makeord(cbox.max.y, vector_MILLIPOINT);
  return 0;
}

int vector_text_setcolour(vector_textobj *p,
                          vdu_palentry f, vdu_palentry b)
{
  if (!p) return -1;

  p->fore = f;
  p->back = b;
  return 0;
}

int vector_text_setfont(vector_textobj *p, const char *f)
{
  void *tmp;
  if (!p) return -1;
  tmp = malloc(strlen(f) + 1);
  if (!tmp) return -1;
  free(p->font);
  p->font = tmp;
  strcpy(p->font, f);
  vector_invalftab((vector_obj *) p);
  vector_calctextbbox(p);
  return 0;
}

int vector_text_settext(vector_textobj *p, const char *t)
{
  void *tmp;
  if (!p) return -1;
  tmp = malloc(strlen(t) + 1);
  if (!tmp) return -1;
  free(p->text);
  p->text = tmp;
  strcpy(p->text, t);
  vector_calctextbbox(p);
  return 0;
}

int vector_text_setscale(vector_textobj *p, vector_ord x, vector_ord y)
{
  if (!p) return -1;
  p->width = x;
  p->height = y;
  if (p->text)
    vector_calctextbbox(p);
  return 0;
}

int vector_text_setinarea(vector_textobj *p,
                          const vector_box *b, unsigned a)
{
  vector_ord diff;
  if (!p || !p->text) return -1;

  vector_getboxtext(p, NULL, 0);
  diff = 0;
  switch (a & 3) {
  case vector_LEFT:
    diff = b->min.x - p->hdr.bbox.min.x;
    break;
  case vector_CENTRE:
    diff = (b->min.x + b->max.x) / 2.0 -
      (p->hdr.bbox.min.x + p->hdr.bbox.max.x) / 2.0;
    break;
  case vector_RIGHT:
    diff = b->max.x - p->hdr.bbox.max.x;
    break;
  }
  p->hdr.bbox.min.x += diff;
  p->hdr.bbox.max.x += diff;
  p->pos.x += diff;
  diff = 0;
  switch (a & 12) {
  case vector_BOTTOM:
    diff = b->min.y - p->hdr.bbox.min.y;
    break;
  case vector_MIDDLE:
    diff = (b->min.y + b->max.y) / 2.0 -
      (p->hdr.bbox.min.y + p->hdr.bbox.max.y) / 2.0;
    break;
  case vector_TOP:
    diff = b->max.y - p->hdr.bbox.max.y;
    break;
  }
  p->hdr.bbox.min.y += diff;
  p->hdr.bbox.max.y += diff;
  p->pos.y += diff;
  vector_invalbbox(p->hdr.parent);
  return 0;
}

void vector_destroytext(vector_textobj *p)
{
  vector_invalbbox(p->hdr.parent);
  vector_invalsize(p->hdr.parent);
  vector_invalftab(p->hdr.parent);
  vector_unlink((vector_obj *) p);
  free(p->font);
  free(p->text);
  free(p);
}

int vector_getsizetext(vector_textobj *p, size_t *sp)
{
  if (!p)
    return -1;

  if (!p->hdr.sizeval) {
    if (p->text) {
      p->hdr.size = sizeof(drawfile_objhdr) + sizeof(drawfile_textobj);
      p->hdr.size += strlen(p->text) + 4;
      p->hdr.size &= ~3;
    } else {
      p->hdr.size = 0;
    }
  }

  if (sp)
    *sp += p->hdr.size;

  if (!p->hdr.sizeval) {
    p->hdr.sizeval = 1;
    vector_invalsize(p->hdr.parent);
  }
  return 0;
}

int vector_writetext(vector_textobj *p,
                     uint8_t **pp, uint8_t *z, vector_fonttab *ft)
{
  drawfile_textobj *op;
  if (!p) return -1;

  vector_getsizetext(p, NULL);
  if (p->hdr.size == 0)
    return 0;

  if (*pp + p->hdr.size > z)
    return -1;

  vector_getboxtext(p, NULL, 0);

  ((drawfile_objhdr *) *pp)->type = drawfile_OTEXT;
  ((drawfile_objhdr *) *pp)->size = p->hdr.size;
  vector_v2dbox(&((drawfile_objhdr *) *pp)->bbox, &p->hdr.bbox);
  *pp += sizeof(drawfile_objhdr);

  op = (drawfile_textobj *) *pp;
  op->fore = p->fore;
  op->back = p->back;
  op->style = p->font ? vector_findfont(ft, p->font) : 0;
  op->width = draw_makeord(p->width, draw_UNIT);
  op->height = draw_makeord(p->height, draw_UNIT);
  op->base.x = draw_makeord(p->pos.x, draw_UNIT);
  op->base.y = draw_makeord(p->pos.y, draw_UNIT);
  *pp += sizeof(drawfile_textobj);

  strcpy((char *) *pp, p->text);
  *pp += strlen(p->text) + 1;
  while ((unsigned) (*pp) & 3)
    *((*pp)++) = '\0';
  return 0;
}

int vector_printtext(vector_textobj *p, FILE *fp, vector_fonttab *ft)
{
  drawfile_objhdr hdr;
  drawfile_textobj obj;
  int i;

  if (!p) return -1;

  vector_getsizetext(p, NULL);
  if (p->hdr.size == 0)
    return 0;

  vector_getboxtext(p, NULL, 0);
  hdr.type = drawfile_OTEXT;
  hdr.size = p->hdr.size;
  vector_v2dbox(&hdr.bbox, &p->hdr.bbox);
  obj.fore = p->fore;
  obj.back = p->back;
  obj.style = p->font ? vector_findfont(ft, p->font) : 0;
  obj.width = draw_makeord(p->width, draw_UNIT);
  obj.height = draw_makeord(p->height, draw_UNIT);
  obj.base.x = draw_makeord(p->pos.x, draw_UNIT);
  obj.base.y = draw_makeord(p->pos.y, draw_UNIT);
  fwrite(&hdr, sizeof hdr, 1, fp);
  fwrite(&obj, sizeof obj, 1, fp);

  i = strlen(p->text) + 1;
  fwrite(p->text, 1, i, fp);
  while (i & 3) {
    i++;
    fputc('\0', fp);
  }

  return 0;
}

int vector_getboxtext(vector_textobj *p, vector_box *bb, unsigned ow)
{
  if (!p || !p->text) return -1;

  if (bb) {
    if (ow) {
#if false
      bb->max.x = p->hdr.bbox.max.x;
      bb->max.y = p->hdr.bbox.max.y;
      bb->min.x = p->hdr.bbox.min.x;
      bb->min.y = p->hdr.bbox.min.y;
#else
      *bb = p->hdr.bbox;
#endif
    } else {
      if (p->hdr.bbox.max.x > bb->max.x)
        bb->max.x = p->hdr.bbox.max.x;
      if (p->hdr.bbox.max.y > bb->max.y)
        bb->max.y = p->hdr.bbox.max.y;
      if (p->hdr.bbox.min.x < bb->min.x)
        bb->min.x = p->hdr.bbox.min.x;
      if (p->hdr.bbox.min.y < bb->min.y)
        bb->min.y = p->hdr.bbox.min.y;
    }
  }
  return 0;
}

int vector_getfontstext(vector_textobj *p, vector_fonttab *ft)
{
#ifdef DEBUG
  fprintf(stderr, "getting font for text\n");
#endif
  if (!p || !p->text) return -1;
#ifdef DEBUG
  fprintf(stderr, "  valid text: %s\n", p->text);
#endif
  if (!p->font) return 0;
#ifdef DEBUG
  fprintf(stderr, "  non-system font: %s\n", p->font);
#endif
  vector_addfont(ft, p->font);
#ifdef DEBUG
  fprintf(stderr, "  font added to table\n");
#endif
  return 0;
}

int vector_translatetext(vector_textobj *p, vector_ord dx, vector_ord dy)
{
  if (!p) return -1;
#if 0
  fprintf(stderr, "translate text(%f, %f)\n",
          dx / vector_inCH, dy / vector_inCH);
#endif

  p->pos.x += dx;
  p->pos.y += dy;
#if 0
  fprintf(stderr, "  pos moved\n");
#endif
  if (p->hdr.bboxval) {
    p->hdr.bbox.min.x += dx;
    p->hdr.bbox.min.y += dy;
    p->hdr.bbox.max.x += dx;
    p->hdr.bbox.max.y += dy;
  }
#if 0
  fprintf(stderr, "  bbox moved\n");
#endif
  vector_invalbbox(p->hdr.parent);
#if 0
  fprintf(stderr, "  parent invalidated\n");
#endif
  return 0;
}
