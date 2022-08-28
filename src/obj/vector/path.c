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
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../riscos/draw/op.h"

#include "../yacitros/vector/generic.h"
#include "../yacitros/vector/intern.h"
#include "../yacitros/vector/path.h"
#include "../yacitros/vector/link.h"

#include "../utils.h"

static int vector_uncachepath(vector_pathobj *p)
{
  if (!p) return -1;
  free(p->cache);
  p->cache = NULL;
  vector_invalbbox((vector_obj *) p);
  vector_invalsize((vector_obj *) p);
  return 0;
}

vector_pathobj *vector_path_create(void)
{
  vector_pathobj *ALLOCATE(r);
  if (!r) return NULL;
  vector_inithdr(&r->hdr, vector_OPATH);
  dllist_init(&r->sps);
  r->cache = NULL;
  r->fill = -1;
  r->line = 0;
  r->style.word = 0x20100042;
  r->thickness = 0;
  return r;
}

static int vector_sizepathdata(vector_pathobj *p, size_t *s)
{
  vector_subpath *sp;
  vector_pathcomp *cp;

  if (!p) return -1;

  for (sp = dllist_first(&p->sps); sp; sp = dllist_next(others, sp))
    if (dllist_first(&sp->comps) != dllist_last(&sp->comps)) {
      for (cp = dllist_first(&sp->comps); cp; cp = dllist_next(others, cp))
        *s += cp->bezier ? 28 : 12;
      *s += dllist_last(&sp->comps)->close ? 4 : 0;
    }
  *s += 4;
  return 0;
}

static int vector_createpathdata(vector_pathobj *p, uint32_t **pp)
{
  vector_subpath *sp;
  vector_pathcomp *cp;

  if (!p) return -1;

  for (sp = dllist_first(&p->sps); sp; sp = dllist_next(others, sp))
    if (dllist_first(&sp->comps) != dllist_last(&sp->comps)) {
      for (cp = dllist_first(&sp->comps); cp; cp = dllist_next(others, cp)) {
        if (cp->bezier) {
          *((*pp)++) = draw_PBEZIER;
          *((*pp)++) = draw_makeord(cp->pos[1].x, draw_UNIT);
          *((*pp)++) = draw_makeord(cp->pos[1].y, draw_UNIT);
          *((*pp)++) = draw_makeord(cp->pos[2].x, draw_UNIT);
          *((*pp)++) = draw_makeord(cp->pos[2].y, draw_UNIT);
          *((*pp)++) = draw_makeord(cp->pos[0].x, draw_UNIT);
          *((*pp)++) = draw_makeord(cp->pos[0].y, draw_UNIT);
        } else if (cp == dllist_first(&sp->comps)) {
#ifdef DEBUG
          fprintf(stderr, "*pp (0) = %p\n", *pp);
#endif
          *((*pp)++) = draw_PMOVE;
          *((*pp)++) = draw_makeord(cp->pos[0].x, draw_UNIT);
          *((*pp)++) = draw_makeord(cp->pos[0].y, draw_UNIT);
#ifdef DEBUG
          fprintf(stderr, "*pp (1) = %p\n", *pp);
#endif
        } else {
          *((*pp)++) = draw_PLINE;
          *((*pp)++) = draw_makeord(cp->pos[0].x, draw_UNIT);
          *((*pp)++) = draw_makeord(cp->pos[0].y, draw_UNIT);
        }
      }
      if (dllist_last(&sp->comps)->close)
        *((*pp)++) = draw_PCLOSE;
    }
  *((*pp)++) = draw_PEND;
  return 0;
}

static int vector_cachepath(vector_pathobj *p)
{
  uint32_t *s;
#ifdef DEBUG
  fprintf(stderr, "cachepath\n");
#endif
  if (!p) return -1;
#ifdef DEBUG
  fprintf(stderr, "p != NULL\n");
#endif
  if (p->cache) return 0;
#ifdef DEBUG
  fprintf(stderr, "not already cached\n");
#endif
  p->size = 0;
  vector_sizepathdata(p, &p->size);
#ifdef DEBUG
  fprintf(stderr, "cache size == %lu\n", (unsigned long) p->size);
#endif
  p->cache = malloc(p->size * sizeof(uint8_t));
  if (!p->cache) {
#if true
    fprintf(stderr, "Warning! Can't allocate %lu for cache.\n",
            (unsigned long) (p->size * sizeof(uint8_t)));
#endif
    return -1;
  }
  s = (uint32_t *) p->cache;
#ifdef DEBUG
  fprintf(stderr, "writing cache to %p %p\n", (void *) s, p->cache);
#endif
  vector_createpathdata(p, &s);
#ifdef DEBUG
  fprintf(stderr, "cache written (end = %p)\n", (void *) s);
#endif
  return 0;
}

static int vector_printpathdata(vector_pathobj *p, FILE *fp)
{
  vector_subpath *sp;
  vector_pathcomp *cp;
  uint32_t word;

  if (!p) return -1;

  for (sp = dllist_first(&p->sps); sp; sp = dllist_next(others, sp))
    if (dllist_first(&sp->comps) != dllist_last(&sp->comps)) {
      for (cp = dllist_first(&sp->comps); cp; cp = dllist_next(others, cp)) {
        if (cp->bezier) {
          word = draw_PBEZIER;
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[1].x, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[1].y, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[2].x, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[2].y, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[0].x, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[0].y, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
#ifdef DEBUG
          fprintf(stderr, " F:(%f, %f)\n", cp->pos[0].x / vector_INCH,
                  cp->pos[0].y / vector_INCH);
          fprintf(stderr, " I:(%f, %f)\n", cp->pos[1].x / vector_INCH,
                  cp->pos[1].y / vector_INCH);
          fprintf(stderr, " O:(%f, %f)\n", cp->pos[2].x / vector_INCH,
                  cp->pos[2].y / vector_INCH);
#endif
        } else if (cp == dllist_first(&sp->comps)) {
          word = draw_PMOVE;
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[0].x, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[0].y, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
        } else {
          word = draw_PLINE;
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[0].x, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
          word = draw_makeord(cp->pos[0].y, draw_UNIT);
          fwrite(&word, sizeof word, 1, fp);
        }
      }
      if (dllist_last(&sp->comps)->close) {
        word = draw_PCLOSE;
        fwrite(&word, sizeof word, 1, fp);
      }
    }
  word = draw_PEND;
  fwrite(&word, sizeof word, 1, fp);
  return 0;
}

int vector_path_setlinecolour(vector_pathobj *p, vdu_palentry c)
{
  if (!p) return -1;

  p->line = c;
  vector_invalbbox((vector_obj *) p);
  return 0;
}

int vector_path_setfillcolour(vector_pathobj *p, vdu_palentry c)
{
  if (!p) return -1;

  p->fill = c;
  vector_invalbbox((vector_obj *) p);
  return 0;
}

int vector_path_setwidth(vector_pathobj *p, vector_ord w)
{
  if (!p) return -1;

  p->thickness = w;
  vector_invalbbox((vector_obj *) p);
  return 0;
}

int vector_path_setjoin(vector_pathobj *p, unsigned s)
{
  if (!p) return -1;

  p->style.bits.join = s;
  vector_invalbbox((vector_obj *) p);
  return 0;
}

int vector_path_setstartcap(vector_pathobj *p, unsigned s)
{
  if (!p) return -1;

  p->style.bits.startcap = s;
  vector_invalbbox((vector_obj *) p);
  return 0;
}

int vector_path_setendcap(vector_pathobj *p, unsigned s)
{
  if (!p) return -1;

  p->style.bits.endcap = s;
  vector_invalbbox((vector_obj *) p);
  return 0;
}

int vector_path_setwind(vector_pathobj *p, unsigned s)
{
  if (!p) return -1;

  p->style.bits.wind = (s == draw_FWINDEO);
  return 0;
}

int vector_path_reset(vector_pathobj *p)
{
  vector_subpath *sp;
  vector_pathcomp *cp;

  if (!p) return -1;

  while ((sp = dllist_first(&p->sps))) {
    while ((cp = dllist_first(&sp->comps))) {
      dllist_unlink(&sp->comps, others, cp);
      free(cp);
    }
    dllist_unlink(&p->sps, others, sp);
    free(sp);
  }
  vector_uncachepath(p);
  return 0;
}

int vector_path_move(vector_pathobj *p, vector_ord x, vector_ord y)
{
  vector_subpath *sp;
  vector_pathcomp *cp;

  sp = dllist_last(&p->sps);
  if (!sp) {
    ALLOCATE(sp);
    if (!sp) return -1;
    dllist_init(&sp->comps);
    dllist_append(&p->sps, others, sp);
  }
  cp = dllist_last(&sp->comps);
  if (!cp) {
    /* if no components */
    ALLOCATE(cp);
    if (!cp) return -1;
    cp->bezier = cp->close = 0;
    cp->pos[0].x = x;
    cp->pos[0].y = y;
    dllist_append(&sp->comps, others, cp);
  } else if (cp == dllist_first(&sp->comps)) {
    /* if one component */
    cp->bezier = cp->close = 0;
    cp->pos[0].x = x;
    cp->pos[0].y = y;
  } else {
    /* if many components */
    ALLOCATE(sp);
    if (!sp) return -1;
    dllist_init(&sp->comps);
    dllist_append(&p->sps, others, sp);
    ALLOCATE(cp);
    if (!cp) return -1;
    cp->bezier = cp->close = 0;
    cp->pos[0].x = x;
    cp->pos[0].y = y;
    dllist_append(&sp->comps, others, cp);
  }
  vector_uncachepath(p);
  return 0;
}

int vector_path_draw(vector_pathobj *p, vector_ord x, vector_ord y)
{
  vector_subpath *sp;
  vector_pathcomp *cp;

  sp = dllist_last(&p->sps);
  if (!sp) return -1;
  if (!dllist_last(&sp->comps)) return -1;
  ALLOCATE(cp);
  if (!cp) return -1;
  cp->bezier = cp->close = 0;
  cp->pos[0].x = x;
  cp->pos[0].y = y;
  cp->pos[1].x = cp->pos[1].y = cp->pos[2].x = cp->pos[2].y = 0.0;
  dllist_append(&sp->comps, others, cp);
  vector_uncachepath(p);
  return 0;
}

int vector_path_bezier(vector_pathobj *p, vector_ord x, vector_ord y,
                       vector_ord ax, vector_ord ay,
                       vector_ord bx, vector_ord by)
{
  vector_subpath *sp;
  vector_pathcomp *cp;

  sp = dllist_last(&p->sps);
  if (!sp) return -1;
  if (!dllist_last(&sp->comps)) return -1;
  ALLOCATE(cp);
  if (!cp) return -1;
  cp->bezier = 1;
  cp->close = 0;
  cp->pos[0].x = x;
  cp->pos[0].y = y;
  cp->pos[1].x = ax;
  cp->pos[1].y = ay;
  cp->pos[2].x = bx;
  cp->pos[2].y = by;
  dllist_append(&sp->comps, others, cp);
  vector_uncachepath(p);
  return 0;
}

int vector_path_arc(vector_pathobj *p,
                    vector_ord x, vector_ord y, vector_ord a)
{
  vector_subpath *sp;
  vector_pathcomp *cp;
  const double factor = 0.55228;
  double length;
  vector_ord lx, ly;
  vector_ord ax, ay, bx, by, cx, cy;
  vector_ord dx, dy;
  vector_ord s;
  double sina = sin(a), cosa = cos(a);

#ifdef DEBUG
  fprintf(stderr, "  Centre: (%f, %f)\n", x / vector_INCH, y / vector_INCH);
#endif
  sp = dllist_last(&p->sps);
  if (!sp) return -1;
  if (!(cp = dllist_last(&sp->comps))) return -1;
  /* get last coords */
  lx = cp->pos[0].x;
  ly = cp->pos[0].y;
#ifdef DEBUG
  fprintf(stderr, "  Origin: (%f, %f)\n", lx / vector_INCH, ly / vector_INCH);
#endif
  dx = lx - x;
  dy = ly - y;
  s = sqrt(dx * dx + dy * dy);
#ifdef DEBUG
  fprintf(stderr, "  Radius: %f\n", s / vector_INCH);
#endif
  bx = -dy / s;
  by = dx / s;
  ax = dx * cosa - dy * sina;
  ay = dy * cosa + dx * sina;
  cx = ay / s;
  cy = -ax / s;
  ax += x;
  ay += y;
#ifdef DEBUG
  fprintf(stderr, "  Final: (%f, %f)\n", ax / vector_INCH, ay / vector_INCH);
#endif
  length = s * factor * a / vector_makeord(90, vector_DEGREE);
#ifdef DEBUG
  fprintf(stderr, "  V-length: %f\n", length / vector_INCH);
#endif
  bx = lx + bx * length;
  by = ly + by * length;
#ifdef DEBUG
  fprintf(stderr, "  In-V: (%f, %f)\n", bx / vector_INCH, by / vector_INCH);
#endif
  cx = ax + cx * length;
  cy = ay + cy * length;
#ifdef DEBUG
  fprintf(stderr, "  Out-V: (%f, %f)\n", cx / vector_INCH, cy / vector_INCH);
#endif
  vector_path_bezier(p, ax, ay, bx, by, cx, cy);
  return 0;
}

int vector_path_close(vector_pathobj *p)
{
  vector_subpath *sp;
  vector_pathcomp *cp, *cp0;

  sp = dllist_last(&p->sps);
  if (!sp) return -1;
  cp = dllist_last(&sp->comps);
  if (!cp) return -1;
  cp->close = 1;
  cp0 = dllist_first(&sp->comps);
  if (cp->bezier) {
    cp->pos[2].x += cp0->pos[0].x - cp->pos[0].x;
    cp->pos[2].y += cp0->pos[0].y - cp->pos[0].y;
  }
  cp->pos[0].x = cp0->pos[0].x;
  cp->pos[0].y = cp0->pos[0].y;
  vector_uncachepath(p);
  return 0;
}

void vector_destroypath(vector_pathobj *p)
{
  vector_path_reset(p);
  vector_unlink((vector_obj *) p);
  free(p);
}

int vector_getsizepath(vector_pathobj *p, size_t *sp)
{
  if (!p) return -1;

  if (!p->hdr.sizeval) {
    if (dllist_isempty(&p->sps)) {
      p->hdr.size = 0;
    } else {
      p->hdr.size = 40;
      vector_sizepathdata(p, &p->hdr.size);
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

int vector_writepath(vector_pathobj *p,
                     uint8_t **pp, uint8_t *z, vector_fonttab *ft)
{
  if (!p) return -1;

  vector_getsizepath(p, NULL);
  if (p->hdr.size == 0)
    return 0;

  vector_getboxpath(p, NULL, 0);
  vector_cachepath(p);

  if (*pp + p->hdr.size > z)
    return -1;

  ((drawfile_objhdr *) *pp)->type = drawfile_OPATH;
  ((drawfile_objhdr *) *pp)->size = p->hdr.size;
  vector_v2dbox(&((drawfile_objhdr *) *pp)->bbox, &p->hdr.bbox);
  *pp += sizeof(drawfile_objhdr);

  ((drawfile_pathobj *) *pp)->fill = p->fill;
  ((drawfile_pathobj *) *pp)->outline = p->line;
  ((drawfile_pathobj *) *pp)->thickness =
    draw_makeord(p->thickness, draw_UNIT);
  ((drawfile_pathobj *) *pp)->style.word = p->style.word;
  *pp += 16;

  memcpy(*pp, p->cache, p->size);
  *pp += p->size;
  return 0;
}

int vector_printpath(vector_pathobj *p, FILE *fp, vector_fonttab *ft)
{
  drawfile_objhdr hdr;
  drawfile_pathobj phdr;
  int gotbox;

  if (!p) return -1;

#ifdef DEBUG
  fprintf(stderr, "vector_printpath()...\n");
#endif

  vector_getsizepath(p, NULL);
  if (p->hdr.size == 0)
    return 0;

#ifdef DEBUG
  fprintf(stderr, "  size got as %u\n", p->hdr.size);
#endif

  gotbox = vector_getboxpath(p, NULL, 0) == 0;
#ifdef DEBUG
  fprintf(stderr, "  bbox got = %d\n", gotbox);
#endif
  if (!gotbox) {
    p->hdr.bbox.min.x = p->hdr.bbox.min.y =
      p->hdr.bbox.max.x = p->hdr.bbox.max.y = 0;
  }

  hdr.type = drawfile_OPATH;
  hdr.size = p->hdr.size;
  vector_v2dbox(&hdr.bbox, &p->hdr.bbox);
  fwrite(&hdr, sizeof hdr, 1, fp);

#ifdef DEBUG
  fprintf(stderr, "  path obj hdr sent -> %p\n", (void *) fp);
#endif

  phdr.fill = p->fill;
  phdr.outline = p->line;
  phdr.thickness = p->thickness;
  phdr.style.word = p->style.word;

#ifdef DEBUG
  fprintf(stderr, "  path hdr ready -> %p\n", fp);
#endif
  fwrite(&phdr, 1, 16, fp);

#ifdef DEBUG
  fprintf(stderr, "  path hdr sent\n");
#endif
  vector_printpathdata(p, fp);

#ifdef DEBUG
  fprintf(stderr, "  path data sent\n");
#endif
  return 0;
}

int vector_getboxpath(vector_pathobj *p, vector_box *bb, unsigned ow)
{
  if (!p) return -1;

#ifdef DEBUG
  fprintf(stderr, "vector_getboxpath()\n");
#endif

  if (!p->hdr.bboxval) {
    if (dllist_isempty(&p->sps)) {
#ifdef DEBUG
      fprintf(stderr, " Bbox invalid.\n");
#endif
      return -1;
    } else {
      _kernel_oserror *ep;
      draw_capjoin cj;
      draw_box bbox;

      /* use Draw SWIs to get bbox */

#ifdef DEBUG
      fprintf(stderr, " Caching path...\n");
#endif
      if (vector_cachepath(p) < 0)
        return -1;
#ifdef DEBUG
      fprintf(stderr, "  calling draw_***...\n");
#endif
      cj.join = p->style.bits.join;
      cj.leadcap = p->style.bits.endcap;
      cj.trailcap = p->style.bits.startcap;
      cj.padding = 0;
      cj.mitre = 1;
      cj.leadw = cj.trailw = p->style.bits.triwidth << 4;
      cj.leadh = cj.trailh = p->style.bits.trihgt << 4;

      ep = draw_processpath_bb(p->cache, 0, NULL, 0,
                               draw_makeord(p->thickness, draw_UNIT),
                               &cj, NULL /* dash */, &bbox, NULL);
      if (ep) {
        fprintf(stderr, "vector: %d %s\n", ep->errnum, ep->errmess);
        return -1;
      }
      p->hdr.bbox.min.x = vector_makeord(bbox.min.x, vector_UNIT);
      p->hdr.bbox.min.y = vector_makeord(bbox.min.y, vector_UNIT);
      p->hdr.bbox.max.x = vector_makeord(bbox.max.x, vector_UNIT);
      p->hdr.bbox.max.y = vector_makeord(bbox.max.y, vector_UNIT);
#ifdef DEBUG
      fprintf(stderr, "  sorted path of size %lu\n",
              (unsigned long) p->size);
      fprintf(stderr, "!minx = %d\n", bbox.min.x);
      fprintf(stderr, "!miny = %d\n", bbox.min.y);
      fprintf(stderr, "!maxx = %d\n", bbox.max.x);
      fprintf(stderr, "!maxy = %d\n", bbox.max.y);
      fprintf(stderr, "minx = %g\n", p->hdr.bbox.min.x);
      fprintf(stderr, "miny = %g\n", p->hdr.bbox.min.y);
      fprintf(stderr, "maxx = %g\n", p->hdr.bbox.max.x);
      fprintf(stderr, "maxy = %g\n", p->hdr.bbox.max.y);
#endif
    }
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

int vector_translatepath(vector_pathobj *p, vector_ord dx, vector_ord dy)
{
  vector_subpath *sp;
  vector_pathcomp *cp;

  if (!p) return -1;
  /* translate subpaths and their components */
  for (sp = dllist_first(&p->sps); sp; sp = dllist_next(others, sp))
    for (cp = dllist_first(&sp->comps); cp; cp = dllist_next(others, cp)) {
#if 1
      cp->pos[0].x += dx;
      cp->pos[0].y += dy;
      if (cp->bezier) {
        cp->pos[1].x += dx;
        cp->pos[1].y += dy;
        cp->pos[2].x += dx;
        cp->pos[2].y += dy;
      }
#endif
    }
  if (p->hdr.bboxval) {
    p->hdr.bbox.min.x += dx;
    p->hdr.bbox.min.y += dy;
    p->hdr.bbox.max.x += dx;
    p->hdr.bbox.max.y += dy;
  }
  vector_invalbbox(p->hdr.parent);
  return 0;
}
