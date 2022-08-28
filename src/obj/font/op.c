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

#include <kernel.h>
#include <swis.h>

#include <riscos/swi/Font.h>

#include "../riscos/font/op.h"

_kernel_oserror *font_find(font_handle *fp, const char *n,
                           const font_dim *d, font_res *r)
{
  return _swix(XFont_FindFont, _INR(1,5) | _OUT(0) | (r?_OUTR(4,5):0),
               n, d->size.x, d->size.y, d->res.x, d->res.y, fp, &r->x, &r->y);
}

_kernel_oserror *font_readdefn(font_handle h, char *n, font_dim *d,
                               int *age, int *used)
{
  font_16thpt ptmp;
  font_dpi dtmp;
  int itmp;
  return _swix(XFont_ReadDefn, _INR(0,1) | _OUTR(2,7), h, n,
               d ? &d->size.x : &ptmp, d ? &d->size.y : &dtmp,
               d ? &d->res.x : &ptmp, d ? &d->res.y : &ptmp,
               age ? age : &itmp, used ? used : &itmp);
}

_kernel_oserror *font_bbox(font_handle h, vdu_box *b)
{
  return b ? _swix(XFont_ReadInfo, _IN(0) | _OUTR(1,4), h,
                   &b->min.x, &b->min.y, &b->max.x, &b->max.y) : NULL;
}

_kernel_oserror *font_c_stringbbox(const char *s, vdu_box *b)
{
  return b ? _swix(XFont_StringBBox, _IN(1) | _OUTR(1,4), s,
                   &b->min.x, &b->min.y, &b->max.x, &b->max.y) : NULL;
}

_kernel_oserror *font_set(font_handle h)
{
  return _swix(XFont_SetFont, _IN(0), h);
}

_kernel_oserror *font_c_get(font_handle *fp, font_cols *c)
{
  return _swix(XFont_CurrentFont, _OUT(0) | (c?_OUTR(1,3):0),
               fp, &c->bg, &c->fg, &c->fgo);
}

_kernel_oserror *font_lose(font_handle h)
{
  return _swix(XFont_LoseFont, _IN(0), h);
}

_kernel_oserror *font_losetab(font_htab t)
{
  _kernel_oserror *ep = NULL;
  font_handle h;

  for (h = 1; !ep && ((0x100u | (unsigned long) h) - 256) < 256; h++)
    while (!ep && t[h] > 0)
      ep = _swix(XFont_LoseFont, _IN(0), h);
  return ep;
}

_kernel_oserror *font_c_paint(const char *s,
                              font_plottype pt, const vdu_point *p)
{
  if (!p) return NULL;
  return _swix(XFont_Paint, _INR(1,4), s, pt, p->x, p->y);
}

_kernel_oserror *font_c_width(const char *s,
                              const font_lim *lim, font_lim *term)
{
  return _swix(XFont_StringWidth, _INR(1,5)|(term?_OUTR(2,5):0),
               s, lim->pos.x, lim->pos.y, lim->split, lim->len,
               &term->pos.x, &term->pos.y, &term->split, &term->len);
}

_kernel_oserror *font_os2mp(const vdu_point *os, vdu_point *mp)
{
  if (!mp || !os) return NULL;
  return _swix(XFont_Converttopoints, _INR(1,2)|_OUTR(1,2),
               os->x, os->y, &mp->x, &mp->y);
}

_kernel_oserror *font_mp2os(const vdu_point *mp, vdu_point *os)
{
  if (!mp || !os) return NULL;
  return _swix(XFont_ConverttoOS, _INR(1,2)|_OUTR(1,2),
               mp->x, mp->y, &os->x, &os->y);
}
