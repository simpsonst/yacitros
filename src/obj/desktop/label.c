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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <kernel.h>
#include <swis.h>

#include <riscos/swi/MessageTrans.h>

#include "../yacitros/desktop/label.h"

#include "../utils.h"
#include "throw.h"

#ifdef Yacitros_desktop_msgtranslabel

int label_open(label_bundle *h, const char *f)
{
  _kernel_swi_regs T;

  T.r[0] = h;
  T.r[1] = f;
  T.r[2] = 0;

  return task_seterr(_kernel_swi(XMessageTrans_OpenFile, &T, &T)) ? -1 : 0;
}

int label_close(label_bundle *h)
{
  _kernel_swi_regs T;

  T.r[0] = h;
  return task_seterr(_kernel_swi(XMessageTrans_CloseFile, &T, &T)) ? -1 : 0;
}

char *label_lookup(label_bundle *h, const char *token,
                   char *buf, size_t *len,
                   const char *i1, const char *i2, const char *i3,
                   const char *i4)
{
  _kernel_swi_regs T;

  T.r[0] = h;
  T.r[1] = token;
  T.r[2] = buf;
  T.r[3] = *len;
  T.r[4] = i1;
  T.r[5] = i2;
  T.r[6] = i3;
  T.r[7] = i4;

  if (_kernel_swi(XMessageTrans_Lookup, &T, &T)) return 0;

  *len = T.r[3];
  return (char *) T.r[2];
}

const char *label_default(label_bundle *h, const char *token, const char *d)
{
  static char tmp[5][1000];
  static int rno = 0;
  int rnold = rno;

  _kernel_swi_regs T;

  T.r[0] = h;
  T.r[1] = token;
  T.r[2] = 0;
  T.r[4] = T.r[5] = T.r[6] = T.r[7] = 0;

  if (task_seterr(_kernel_swi(XMessageTrans_Lookup, &T, &T)) ||
      !T.r[2])
    return d;

  memcpy(tmp[rno], (const char *) T.r[2], T.r[3]);
  tmp[rno][T.r[3]] = '\0';

  rno = (rno == sizeof tmp / sizeof tmp[0] - 1 ? 0 : rno + 1);
  return tmp[rnold];
}

#else

struct label_node {
  struct label_node *child[2];
  char *token, *exp;
};

static struct label_node **find_node(struct label_node **rp, const char *s)
{
  int cmp;

  if (!rp) return NULL;
tryit:
  if (!*rp) return rp;
  cmp = strcmp(s, (*rp)->token);
  if (!cmp) return rp;
  rp = &(*rp)->child[cmp > 0];
  goto tryit;
}

int label_open(label_bundle *h, const char *f)
{
  static char line[500];
  char *token, *exp;
  FILE *fp;

  fp = fopen(f, "r");
  if (!fp) {
    task_seterr(NULL);
    return -1;
  }
  h->root = NULL;
  while (!feof(fp)) {
    struct label_node **fnp;
    fgets(line, sizeof line, fp);
    token = line;
    while (*token && isspace(*token)) token++;
    if (*token == '#') continue;
    exp = strchr(token, ':');
    if (!exp) continue;
    *(exp++) = '\0';
    fnp = find_node(&h->root, token);
    if (!*fnp) {
      int explen = strlen(exp);
      if (exp[explen - 1] == '\n')
        exp[--explen] = '\0';
      ALLOCATE(*fnp);
      if (!*fnp) {
        fclose(fp);
        IGNOREI(label_close(h));
        task_seterr(NULL);
        return -1;
      }
      (*fnp)->token = malloc(strlen(token) + 1);
      (*fnp)->exp = malloc(explen + 1);
      if (!(*fnp)->token || !(*fnp)->exp) {
        free((*fnp)->token);
        free((*fnp)->exp);
        free(*fnp);
        fclose(fp);
        IGNOREI(label_close(h));
        task_seterr(NULL);
        return -1;
      }
      (*fnp)->child[0] = (*fnp)->child[1] = NULL;
      strcpy((*fnp)->token, token);
      strcpy((*fnp)->exp, exp);
    }
  }
  fclose(fp);
  return 0;
}

static void delete_node(struct label_node *n)
{
  if (!n) return;
  delete_node(n->child[0]);
  delete_node(n->child[1]);
  free(n->token);
  free(n->exp);
  free(n);
}

int label_close(label_bundle *h)
{
  if (!h) return 0;

  delete_node(h->root);
  h->root = NULL;
  return 0;
}

char *label_lookup(label_bundle *h, const char *token,
                   char *buf, size_t *len,
                   const char *i1, const char *i2, const char *i3,
                   const char *i4)
{
  sprintf(buf, "%.*s", (int) (*len - 1), "label_lookup is not implemented!");
  return buf;
}

const char *label_default(label_bundle *h, const char *token, const char *d)
{
  struct label_node **fnp = find_node(&h->root, token);
  if (!fnp || !*fnp) return d;
  return (*fnp)->exp;
}
#endif
