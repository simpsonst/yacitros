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
#include <stdbool.h>

#include "../riscos/drawfile/types.h"

#include "../yacitros/vector/intern.h"
#include "../yacitros/vector/group.h"
#include "../yacitros/vector/link.h"
#include "../yacitros/vector/generic.h"

#include "../utils.h"

vector_groupobj *vector_group_create(void)
{
  vector_groupobj *ALLOCATE(r);
  if (!r) return NULL;
  vector_inithdr(&r->hdr, vector_OGROUP);
  dllist_init(&r->list);
  memset(r->name, ' ', 12);
  return r;
}

int vector_group_setname(vector_groupobj *p, const char *n)
{
  strncpy(p->name, n, 12);
  return 0;
}

void vector_destroygroup(vector_groupobj *p)
{
  vector_obj *i;
#ifdef DEBUG
  fprintf(stderr, "Destroying group:\n");
#endif
  while ((i = dllist_first(&p->list)))
    vector_destroy(i);
#ifdef DEBUG
  fprintf(stderr, " (group comps destroyed)\n");
#endif

  vector_invalbbox(p->hdr.parent);
  vector_invalsize(p->hdr.parent);
  vector_invalftab(p->hdr.parent);
  vector_unlink((vector_obj *) p);
  free(p);
#ifdef DEBUG
  fprintf(stderr, "group destroyed\n");
#endif
}

int vector_getsizegroup(vector_groupobj *p, size_t *sp)
{
  if (!p->hdr.sizeval) {
    if (dllist_isempty(&p->list)) {
      p->hdr.size = 0;
    } else {
      vector_obj *i;

      p->hdr.size = 0;
      for (i = dllist_first(&p->list); i; i = vector_getnext(i))
        vector_getsize(i, &p->hdr.size);
      if (p->hdr.size)
        p->hdr.size += 36;
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

int vector_writegroup(vector_groupobj *p, uint8_t **pp, uint8_t *z,
                      vector_fonttab *ft)
{
  vector_obj *i;

  /* make size valid */
  vector_getsizegroup(p, NULL);
  if (p->hdr.size == 0)
    return 0;

  /* make bounding box valid */
  vector_getboxgroup(p, NULL, 0);

  /* don't write beyond buffer */
  if (*pp + p->hdr.size > z)
    return -1;

  /* write group header */
  ((drawfile_objhdr *) *pp)->type = drawfile_OGROUP;
  ((drawfile_objhdr *) *pp)->size = p->hdr.size;
  vector_v2dbox(&((drawfile_objhdr *) *pp)->bbox, &p->hdr.bbox);
  *pp += sizeof(drawfile_objhdr);
  memcpy(*pp, p->name, 12);
  *pp += 12;

  for (i = dllist_first(&p->list); i; i = vector_getnext(i))
    vector_write(i, pp, z, ft);

  return 0;
}

int vector_printgroup(vector_groupobj *p, FILE *fp, vector_fonttab *ft)
{
  vector_obj *i;
  drawfile_objhdr head;

#ifdef DEBUG
  fprintf(stderr, "printing group...\n");
#endif

  /* make size valid */
  vector_getsizegroup(p, NULL);
  if (p->hdr.size == 0)
    return 0;

  /* make bounding box valid */
  vector_getboxgroup(p, NULL, 0);

#ifdef DEBUG
  fprintf(stderr, "  box got\n");
#endif

#ifdef DEBUG
  fprintf(stderr, "  size got\n");
#endif

  /* write group header */
  head.type = drawfile_OGROUP;
  head.size = p->hdr.size;
  vector_v2dbox(&head.bbox, &p->hdr.bbox);
#ifdef DEBUG
  fprintf(stderr, "  header made\n");
#endif
  fwrite(&head, sizeof head, 1, fp);
#ifdef DEBUG
  fprintf(stderr, "  hdr written\n");
#endif
  fwrite(p->name, 1, 12, fp);
#ifdef DEBUG
  fprintf(stderr, "  name written\n");
#endif

  for (i = dllist_first(&p->list); i; i = vector_getnext(i))
    vector_print(i, fp, ft);

#ifdef DEBUG
  fprintf(stderr, "  components written\n");
#endif

  return 0;
}

int vector_getboxgroup(vector_groupobj *p, vector_box *bb, unsigned ow)
{
  if (!p)
    return -1;

  if (!p->hdr.bboxval) {
    vector_obj *i;
    int doinit = true;

    for (i = dllist_first(&p->list); i; i = vector_getnext(i))
      if (vector_getbox(i, &p->hdr.bbox, doinit) == 0)
        doinit = false;

    if (doinit)
      return -1;
  }

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

  if (!p->hdr.bboxval) {
    p->hdr.bboxval = 1;
    vector_invalbbox(p->hdr.parent);
  }
  return 0;
}

int vector_getfontsgroup(vector_groupobj *p, vector_fonttab *ft)
{
  vector_obj *i;

  if (!dllist_first(&p->list))
    return -1;

  for (i = dllist_first(&p->list); i; i = vector_getnext(i))
    vector_getfonts(i, ft);

  p->hdr.ftabval = 1;
  return 0;
}

vector_obj *vector_group_getfirst(vector_groupobj *p)
{
  return p ? dllist_first(&p->list) : NULL;
}

vector_obj *vector_group_getlast(vector_groupobj *p)
{
  return p ? dllist_last(&p->list) : NULL;
}

int vector_translategroup(vector_groupobj *p,
                          vector_ord dx, vector_ord dy)
{
  vector_obj *i;

  if (!p) return -1;

  if (!dllist_first(&p->list))
    return -1;

  /* write components */
  for (i = dllist_first(&p->list); i; i = vector_getnext(i))
    vector_translate(i, dx, dy);

  return 0;
}
