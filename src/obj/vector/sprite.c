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
#include <stdlib.h>

#include "../riscos/sprite/op.h"
#include "../riscos/sprite/optypes.h"
#include "../riscos/sprite/args.h"

#include "../yacitros/vector/intern.h"
#include "../yacitros/vector/generic.h"
#include "../yacitros/vector/sprite.h"
#include "../yacitros/vector/link.h"

#include "../utils.h"

vector_spriteobj *vector_sprite_create(void)
{
  vector_spriteobj *ALLOCATE(r);
  if (!r) return NULL;
  vector_inithdr(&r->hdr, vector_OSPRITE);
  r->ptr = NULL;
  return r;
}

int vector_sprite_setimage_sys(vector_spriteobj *p, const char *n)
{
  return -1;
}

int vector_sprite_setimage_wimp(vector_spriteobj *p, const char *n)
{
  return -1;
}

int vector_sprite_setimage_user(vector_spriteobj *p, const char *n,
                                sprite_area a)
{
  sprite_args args;
  args.spec.byname.area = a;
  args.spec.byname.name = n;
  if (sprite_nameop(sprite_Select_Sprite, &args, &args))
    return -1;

  vector_sprite_setimage_ptr(p, args.spec.byaddr.addr, a);
  return 0;
}

int vector_sprite_setimage_ptr(vector_spriteobj *p, sprite_ptr s,
                               sprite_area a)
{
  sprite_args args;
  if (!p || !s) return -1;
  free(p->ptr);

  p->ptr = malloc(s->next);
  if (!p->ptr) return -1;
  memcpy(p->ptr, s, s->next);
  args.spec.byaddr.area = a;
  args.spec.byaddr.addr = s;
  if (sprite_ptrop(sprite_Read_Sprite_Info, &args, &args))
    return -1;
  p->hdr.bbox.min.x = p->hdr.bbox.min.y = draw_makeord(0, draw_UNIT);
  p->hdr.bbox.max.x = draw_makeord(args.dims.width, draw_MM);
  p->hdr.bbox.max.y = draw_makeord(args.dims.height, draw_MM);
  vector_invalbbox(p->hdr.parent);
  p->hdr.bboxval = 1;
  vector_invalsize((vector_obj *) p);
  return 0;
}

int vector_sprite_setinarea(vector_spriteobj *p, const vector_box *b)
{
  p->hdr.bbox = *b;
  p->hdr.bboxval = 1;
  vector_invalbbox(p->hdr.parent);
  return 0;
}

void vector_destroysprite(vector_spriteobj *p)
{
  vector_invalbbox(p->hdr.parent);
  vector_invalsize(p->hdr.parent);
  vector_unlink((vector_obj *) p);
  free(p->ptr);
  free(p);
}

int vector_getsizesprite(vector_spriteobj *p, size_t *sp)
{
  if (!p) return -1;

  if (!p->hdr.sizeval) {
    if (p->ptr) {
      p->hdr.size = sizeof(drawfile_objhdr);
      p->hdr.size += p->ptr->next;
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

int vector_writesprite(vector_spriteobj *p,
                       uint8_t **pp, uint8_t *z, vector_fonttab *ft)
{
  if (!p) return -1;

  vector_getsizesprite(p, NULL);
  if (p->hdr.size == 0)
    return 0;

  if (*pp + p->hdr.size > z)
    return -1;

  vector_getboxsprite(p, NULL, 0);

  ((drawfile_objhdr *) *pp)->type = drawfile_OSPRITE;
  ((drawfile_objhdr *) *pp)->size = p->hdr.size;
  vector_v2dbox(&((drawfile_objhdr *) *pp)->bbox, &p->hdr.bbox);
  *pp += sizeof(drawfile_objhdr);

  memcpy(*pp, p->ptr, p->ptr->next);
  *pp += p->ptr->next;
  return 0;
}

int vector_printsprite(vector_spriteobj *p, FILE *fp, vector_fonttab *ft)
{
  drawfile_objhdr hdr;

  if (!p) return -1;

  vector_getsizesprite(p, NULL);
  if (p->hdr.size == 0)
    return 0;

  vector_getboxsprite(p, NULL, 0);
  hdr.type = drawfile_OSPRITE;
  hdr.size = p->hdr.size;
  vector_v2dbox(&hdr.bbox, &p->hdr.bbox);
  fwrite(&hdr, sizeof hdr, 1, fp);
  fwrite(p->ptr, p->ptr->next, 1, fp);

  return 0;
}

int vector_getboxsprite(vector_spriteobj *p, vector_box *bb, unsigned ow)
{
  if (!p || !p->ptr) return -1;

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

int vector_translatesprite(vector_spriteobj *p,
                           vector_ord dx, vector_ord dy)
{
  if (!p) return -1;

  p->hdr.bbox.min.x += dx;
  p->hdr.bbox.min.y += dy;
  p->hdr.bbox.max.x += dx;
  p->hdr.bbox.max.y += dy;
  vector_invalbbox(p->hdr.parent);
  return 0;
}
