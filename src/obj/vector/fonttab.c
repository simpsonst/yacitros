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
#include <ctype.h>

#include "../yacitros/vector/fonttab.h"

#include "../utils.h"

static int strcmpnc(const char *a, const char *b)
{
  while (*a && toupper(*a) == toupper(*b))
    a++, b++;
  return toupper(*a) - toupper(*b);
}

static int vector_getfonttabsize_r(vector_fonttab *ft, size_t *sp)
{
  if (!*ft) return 0;
  *sp += 2 + strlen((*ft)->name);
  vector_getfonttabsize_r(&(*ft)->left, sp);
  vector_getfonttabsize_r(&(*ft)->right, sp);
  return 0;
}

int vector_getfonttabsize(vector_fonttab *ft, size_t *sp)
{
  if (!ft) return -1;
  if (!*ft) return 0;

  vector_getfonttabsize_r(ft, sp);
  *sp += 11;
  *sp &= ~3;
  return 0;
}

static int vector_printfonttab_r(vector_fonttab *ft, FILE *fp)
{
  int count = 2;

  if (!*ft) return 0;

  fputc((*ft)->id, fp);
  count += fprintf(fp, "%s", (*ft)->name);
  fputc('\0', fp);

  count += vector_printfonttab_r(&(*ft)->left, fp);
  count += vector_printfonttab_r(&(*ft)->right, fp);
  return count;
}

int vector_printfonttab(vector_fonttab *ft, FILE *fp)
{
  struct {
    drawfile_otype type;
    size_t size;
  } hdr;
  int count = 8;

  if (!ft) return -1;
  if (!*ft) return 0;
#ifdef DEBUG
  fprintf(stderr, "printfonttab:\n");
#endif
  hdr.size = 0;
  if (vector_getfonttabsize(ft, &hdr.size) < 0)
    return 0;
#ifdef DEBUG
  fprintf(stderr, "  size obtained (%u)\n", hdr.size);
#endif
  hdr.type = drawfile_OFONTTAB;
  fwrite(&hdr, sizeof hdr, 1, fp);
#ifdef DEBUG
  fprintf(stderr, "  font header written\n");
#endif
  vector_renumberfonttab(ft);
#ifdef DEBUG
  fprintf(stderr, "  fonts renumbered\n");
#endif
  count += vector_printfonttab_r(ft, fp);
#ifdef DEBUG
  fprintf(stderr, "  fonts printed:\n");
#endif
  count = hdr.size - count;
  while (count-- > 0)
    fputc('\0', fp);
#ifdef DEBUG
  fprintf(stderr, "end of font print\n");
#endif
  return 0;
}

static int vector_writefonttab_r(vector_fonttab *ft, uint8_t **pp, uint8_t *z)
{
  int count = 2;
  if (!*ft) return 0;

  *((*pp)++) = (*ft)->id;
  strcpy((char *) *pp, (*ft)->name);
  *pp += strlen((*ft)->name) + 1;

  count += vector_writefonttab_r(&(*ft)->left, pp, z);
  count += vector_writefonttab_r(&(*ft)->right, pp, z);
  return count;
}

int vector_writefonttab(vector_fonttab *ft, uint8_t **pp, uint8_t *z)
{
  struct {
    drawfile_otype type;
    size_t size;
  } hdr;
  int count = 8;

  if (!ft) return -1;
  if (!*ft) return 0;
  if (vector_getfonttabsize(ft, &hdr.size) < 1)
    return 0;
  if (*pp + hdr.size > z)
    return -1;
  hdr.type = drawfile_OFONTTAB;
  memcpy(*pp, &hdr, sizeof hdr);
  *pp += sizeof hdr;

  vector_renumberfonttab(ft);
  count += vector_writefonttab_r(ft, pp, z);
  count = hdr.size - count;
  while (count-- > 0)
    *((*pp)++) = '\0';
  return 0;
}

int vector_createfonttab(vector_fonttab *ft)
{
  *ft = NULL;
  return 0;
}

int vector_deletefonttab(vector_fonttab *ft)
{
  if (ft && *ft) {
    vector_deletefonttab(&(*ft)->left);
    vector_deletefonttab(&(*ft)->right);
    free((*ft)->name);
    free(*ft);
    *ft = NULL;
  }
  return 0;
}

int vector_addfont(vector_fonttab *ft, const char *n)
{
  if (!ft)
    return -1;

  if (*ft) {
    int cmp = strcmpnc(n, (*ft)->name);

    if (cmp < 0)
      return vector_addfont(&(*ft)->left, n);
    else if (cmp > 0)
      return vector_addfont(&(*ft)->right, n);
    else
      return 0;
  } else {
    ALLOCATE(*ft);
    if (!*ft) return -1;
    (*ft)->left = (*ft)->right = NULL;
    (*ft)->name = malloc(strlen(n) + 1);
    if (!(*ft)->name) {
      free(*ft), *ft = NULL;
      return -1;
    }
    strcpy((*ft)->name, n);
    return 0;
  }
}

static int vector_renumberfonttab_n(vector_fonttab *ft, unsigned n)
{
  if (!ft) return -1;
  if (!*ft) return n;

  (*ft)->id = n++;
#ifdef DEBUG
  fprintf(stderr, "    %s -> %u\n", (*ft)->name, (*ft)->id);
#endif
  n = vector_renumberfonttab_n(&(*ft)->left, n);
  return vector_renumberfonttab_n(&(*ft)->right, n);
}

int vector_renumberfonttab(vector_fonttab *ft)
{
  return vector_renumberfonttab_n(ft, 1);
}

unsigned vector_findfont(vector_fonttab *ft, const char *n)
{
  if (!ft)
    return -1;

  if (*ft) {
    int cmp = strcmpnc(n, (*ft)->name);

#ifdef DEBUG
    fprintf(stderr, "    %s - %s == %d\n", n, (*ft)->name, cmp);
#endif
    if (cmp < 0)
      return vector_findfont(&(*ft)->left, n);
    else if (cmp > 0)
      return vector_findfont(&(*ft)->right, n);
    else
      return (*ft)->id;
  } else {
    return 0;
  }
}
