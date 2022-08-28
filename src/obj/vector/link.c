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

#include "../yacitros/vector/generic.h"
#include "../yacitros/vector/link.h"

int vector_succeed(vector_obj *ch, vector_obj *sib)
{
  vector_obj *par;
  if (!ch || ch->hdr.parent || !sib) return -1;
  if (!(par = sib->hdr.parent)) return -1;

  switch (par->hdr.type) {
  case vector_OGROUP:
    ch->hdr.parent = par;
    dllist_insertafter(&((vector_groupobj *) par)->list,
                       hdr.others, sib, ch);
    vector_invalbbox(par);
    vector_invalsize(par);
    vector_invalftab(par);
    return 0;
  case vector_OFILE:
    ch->hdr.parent = par;
    dllist_insertafter(&((vector_fileobj *) par)->list,
                       hdr.others, sib, ch);
    vector_invalbbox(par);
    vector_invalsize(par);
    vector_invalftab(par);
    return 0;
  default:
    return -1;
  }
}

int vector_precede(vector_obj *ch, vector_obj *sib)
{
  vector_obj *par;
  if (!ch || ch->hdr.parent || !sib) return -1;
  if (!(par = sib->hdr.parent)) return -1;
  switch (par->hdr.type) {
  case vector_OGROUP:
    ch->hdr.parent = par;
    dllist_insertbefore(&((vector_groupobj *) par)->list, hdr.others, sib, ch);
    vector_invalbbox(par);
    vector_invalsize(par);
    vector_invalftab(par);
  case vector_OFILE:
    ch->hdr.parent = par;
    dllist_insertbefore(&((vector_fileobj *) par)->list, hdr.others, sib, ch);
    vector_invalbbox(par);
    vector_invalsize(par);
    vector_invalftab(par);
    return 0;
  default:
    return -1;
  }
}

int vector_append(vector_obj *ch, vector_obj *par)
{
  if (ch->hdr.parent)
    return -1;
  switch (par->hdr.type) {
  case vector_OGROUP:
    ch->hdr.parent = par;
    dllist_append(&((vector_groupobj *) par)->list, hdr.others, ch);
    vector_invalbbox(par);
    vector_invalsize(par);
    vector_invalftab(par);
    return 0;
  case vector_OFILE:
    ch->hdr.parent = par;
    dllist_append(&((vector_fileobj *) par)->list, hdr.others, ch);
    vector_invalbbox(par);
    vector_invalsize(par);
    vector_invalftab(par);
    return 0;
  default:
    return -1;
  }
}

int vector_prepend(vector_obj *ch, vector_obj *par)
{
  if (ch->hdr.parent)
    return -1;
  switch (par->hdr.type) {
  case vector_OGROUP:
    ch->hdr.parent = par;
    dllist_prepend(&((vector_groupobj *) par)->list, hdr.others, ch);
    vector_invalbbox(par);
    vector_invalsize(par);
    vector_invalftab(par);
    return 0;
  case vector_OFILE:
    ch->hdr.parent = par;
    dllist_prepend(&((vector_fileobj *) par)->list, hdr.others, ch);
    vector_invalbbox(par);
    vector_invalsize(par);
    vector_invalftab(par);
    return 0;
  default:
    return -1;
  }
}

int vector_unlink(vector_obj *ch)
{
  if (!ch->hdr.parent)
    return -1;
  switch (ch->hdr.parent->hdr.type) {
  case vector_OGROUP:
    vector_invalbbox(ch->hdr.parent);
    vector_invalsize(ch->hdr.parent);
    vector_invalftab(ch->hdr.parent);
    dllist_unlink(&((vector_groupobj *) ch->hdr.parent)->list,
                  hdr.others, ch);
    ch->hdr.parent = NULL;
    return 0;
  case vector_OFILE:
    vector_invalbbox(ch->hdr.parent);
    vector_invalsize(ch->hdr.parent);
    vector_invalftab(ch->hdr.parent);
    dllist_unlink(&((vector_fileobj *) ch->hdr.parent)->list,
                  hdr.others, ch);
    ch->hdr.parent = NULL;
    return 0;
  default:
    return -1;
  }
}

vector_obj *vector_getnext(vector_obj *p)
{
  if (!p || !p->hdr.parent)
    return NULL;

  return dllist_next(hdr.others, p);
}

vector_obj *vector_getprevious(vector_obj *p)
{
  if (!p || !p->hdr.parent)
    return NULL;

  return dllist_prev(hdr.others, p);
}

vector_obj *vector_getparent(vector_obj *p)
{
  return p ? p->hdr.parent : NULL;
}
