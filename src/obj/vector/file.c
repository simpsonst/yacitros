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

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../yacitros/vector/intern.h"
#include "../yacitros/vector/group.h"
#include "../yacitros/vector/fonttab.h"
#include "../yacitros/vector/generic.h"
#include "../yacitros/vector/link.h"
#include "../yacitros/vector/file.h"

#include "../utils.h"

vector_fileobj *vector_file_create(void)
{
  vector_fileobj *ALLOCATE(r);
  if (!r) return NULL;
  vector_inithdr(&r->hdr, vector_OFILE);
  dllist_init(&r->list);
  vector_createfonttab(&r->ftab);
  return r;
}

void vector_destroyfile(vector_fileobj *p)
{
  vector_obj *i;
#ifdef DEBUG
  fprintf(stderr, "Destroying file...\n");
#endif

  while ((i = dllist_first(&p->list)))
    vector_destroy(i);
#ifdef DEBUG
  fprintf(stderr, "File comps destroyed...\n");
#endif

  free(p);
#ifdef DEBUG
  fprintf(stderr, "File destroyed...\n");
#endif
}

static int vector_file_ensurefonts(vector_fileobj *p)
{
  vector_obj *i;

  if (!p) return -1;
  if (p->hdr.ftabval) return 0;

  /* delete the current font table */
  vector_deletefonttab(&p->ftab);
  vector_createfonttab(&p->ftab);

  /* call components to form new one */
  for (i = dllist_first(&p->list); i; i = vector_getnext(i))
    vector_getfonts(i, &p->ftab);
  p->hdr.ftabval = 1;
  return 0;
}

int vector_getsizefile(vector_fileobj *p, size_t *sp)
{
  vector_obj *i;

#if false
  if (!dllist_first(&p->list))
    return -1;
#endif

  if (!p->hdr.sizeval || !p->hdr.ftabval) {
    /* set minimum size */
    p->hdr.size = 40;

    /* create font table */
    vector_file_ensurefonts(p);

    /* add size of table */
    vector_getfonttabsize(&p->ftab, sp);

    for (i = dllist_first(&p->list); i; i = vector_getnext(i))
      vector_getsize(i, &p->hdr.size);
  }

  if (sp)
    *sp += p->hdr.size;

  if (!p->hdr.sizeval || !p->hdr.ftabval) {
    p->hdr.sizeval = 1;
    /* vector_invalsize(p->hdr.parent); */
  }
  return 0;
}

int vector_getboxfile(vector_fileobj *p, vector_box *bb, unsigned ow)
{
  if (!p) return -1;

  if (!p->hdr.bboxval) {
    vector_obj *i;
    int doinit = true;

    for (i = dllist_first(&p->list); i; i = vector_getnext(i))
      if (vector_getbox(i, &p->hdr.bbox, doinit) == 0)
        doinit = false;

    /* Even if there are no components, the file still needs a valid
       bounding box. */
    if (doinit)
      p->hdr.bbox.min.x = p->hdr.bbox.min.y =
        p->hdr.bbox.max.x = p->hdr.bbox.max.y = 0.0;
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

int vector_writefile(vector_fileobj *p,
                     uint8_t **pp, uint8_t *z, vector_fonttab *ft)
{
  vector_obj *i;

#if false
  if (!dllist_first(&p->list))
    return -1;
#endif

  /* ensure size of file */
  vector_getsizefile(p, NULL);

  /* ensure file fits in memory */
  if (*pp + p->hdr.size > z)
    return -1;

  vector_getboxfile(p, NULL, 0);

  /* write header */
  ((drawfile_hdr *) *pp)->magic = drawfile_MAGIC;
  ((drawfile_hdr *) *pp)->major = 201;
  ((drawfile_hdr *) *pp)->minor = 0;
  memcpy(((drawfile_hdr *) *pp)->source, "Yacitros    ", 12);
  vector_v2dbox(&((drawfile_hdr *) *pp)->bbox, &p->hdr.bbox);

  pp += sizeof(drawfile_hdr);

  vector_file_ensurefonts(p);
  /* write font table */
  vector_writefonttab(&p->ftab, pp, z);

  /* write components */
  for (i = dllist_first(&p->list); i; i = vector_getnext(i))
    vector_write(i, pp, z, &p->ftab);

  return 0;
}

int vector_printfile(vector_fileobj *p, FILE *fp, vector_fonttab *ft)
{
  vector_obj *i;
  drawfile_hdr hdr;

#ifdef DEBUG
  fprintf(stderr, "vector_printfile... -> %p\n", (void *) fp);
#endif

#ifdef DEBUG
  fprintf(stderr, "  has elements\n");
#endif

  vector_getboxfile(p, NULL, 0);

#ifdef DEBUG
  fprintf(stderr, "  box got\n");
#endif

  /* write header */
  hdr.magic = drawfile_MAGIC;
  hdr.major = 201;
  hdr.minor = 0;
  memcpy(hdr.source, "Yacitros    ", 12);
  vector_v2dbox(&hdr.bbox, &p->hdr.bbox);
  fwrite(&hdr, sizeof hdr, 1, fp);

#ifdef DEBUG
  fprintf(stderr, "  wrote header\n");
#endif

  vector_file_ensurefonts(p);

#ifdef DEBUG
  fprintf(stderr, "  fonts ensured\n");
#endif
  /* write font table */
  vector_printfonttab(&p->ftab, fp);

#ifdef DEBUG
  fprintf(stderr, "  font table printed\n");
#endif

  /* write components */
  for (i = dllist_first(&p->list); i; i = vector_getnext(i))
    vector_print(i, fp, &p->ftab);

#ifdef DEBUG
  fprintf(stderr, "  all done\n");
#endif

  return 0;
}

int vector_file_getsize(vector_fileobj *p, size_t *sp)
{
  return vector_getsizefile(p, sp);
}

int vector_file_write(vector_fileobj *p, uint8_t **pp, uint8_t *z)
{
  return vector_writefile(p, pp, z, NULL);
}

int vector_file_print(vector_fileobj *p, FILE *fp)
{
  return vector_printfile(p, fp, NULL);
}

vector_obj *vector_file_getfirst(vector_fileobj *p)
{
  return p ? dllist_first(&p->list) : NULL;
}

vector_obj *vector_file_getlast(vector_fileobj *p)
{
  return p ? dllist_last(&p->list) : NULL;
}

int vector_translatefile(vector_fileobj *p, vector_ord dx, vector_ord dy)
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
