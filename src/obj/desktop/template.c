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

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <ddslib/dllist.h>

#include "../riscos/wimp/op.h"

#include "../yacitros/desktop/template.h"

#include "../utils.h"

const char *template_filename = NULL;

void template_init(const char *s) { template_filename = s; }
void template_term(void) { template_filename = NULL; }

template_handle template_load(const char *f, int *pos,
                              size_t icons, size_t space)
{ return template_loadwf(f, pos, icons, space, NULL); }

template_handle template_loadwf(const char *f, int *pos, size_t icons,
                                size_t space, font_htab fh)
{
  _kernel_oserror *ep;
  int zero = 0;
  size_t used;
  char name[12];
  struct template *h;

  if (!template_filename) return NULL;
  ep = wimp_opentemplate(template_filename);
  if (ep) {
    wimp_errflags ef;
    ef.word = 0;
    /* report error ... */
    wimp_reporterror(ep, ef, "Template Module");
    return NULL;
  }

  ALLOCATE(h);
  if (!h) return NULL;

  h->info = malloc(wimp_winsize(icons) + space);
  if (!h->info) { free(h); return NULL; }

  h->ws = malloc(space);
  if (!h->ws) {
    free(h->info);
    free(h);
    return NULL;
  }
  strncpy(name, f, 12);
  ep = wimp_loadtemplate(h->info, h->ws, space, fh,
                         name, pos ? pos : &zero, &used);
  if (ep) {
    wimp_errflags ef;
    ef.word = 0;
    /* report error ... */
    wimp_reporterror(ep, ef, "Template Module");
    free(h->ws);
    free(h->info);
    free(h);
    return NULL;
  }
  /* highly dubious */
  h->ws = realloc(h->ws, used);
  h->wslen = used;
  return h;
}

void *template_release(template_handle h)
{
  void *ws;
  if (!h) return NULL;
  ws = h->ws;
  free(h->info);
  free(h);
  return ws;
}

static void template_moveicon(ptrdiff_t offset, wimp_iconflags *flags,
                              wimp_icondata *data)
{
  if (!flags->bits_colour.indirected)
    return;

  if (flags->bits_colour.text) {
    if ((int) data->indirected_text.val != -1)
      data->indirected_text.val += offset;
    data->indirected_text.buffer += offset;
  } else {
    if (data->indirected_sprite.length > 0)
      data->indirected_sprite.id.name += offset;
  }
}

void template_setsprites(template_handle h, sprite_area sa)
{
  for (size_t ino = 0; ino < h->info->icons; ino++) {
    wimp_iconstate *ptr = &wimp_winicons(h->info)[ino];
    if (ptr->flags.bits_font.sprite &&
        !ptr->flags.bits_font.text &&
        ptr->flags.bits_font.indirected &&
        (int) ptr->data.indirected_sprite.spritearea != 1)
      ptr->data.indirected_sprite.spritearea = sa;
  }
}

template_handle template_copy(template_handle h)
{
  struct template *n;
  ptrdiff_t offset;

  if (!h) return NULL;

  ALLOCATE(n);
  if (!n) return NULL;

  n->info = malloc(wimp_winsize(h->info->icons));
  n->ws = malloc(h->wslen);
  if (!n->info || !n->ws) {
    free(n->info);
    free(n->ws);
    free(n);
    return NULL;
  }

  n->wslen = h->wslen;
  memcpy(n->ws, h->ws, h->wslen);
  memcpy(n->info, h->info, wimp_winsize(h->info->icons));

  /* redirect pointers */
  offset = (char *) n->ws - (char *) h->ws;

  /* title */
  template_moveicon(offset, &n->info->title_flags, &n->info->title_data);
  for (size_t ino = 0; ino < h->info->icons; ino++)
    template_moveicon(offset, &wimp_winicons(n->info)[ino].flags,
                      &wimp_winicons(n->info)[ino].data);
  return n;
}
