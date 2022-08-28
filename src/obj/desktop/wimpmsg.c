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
#include <assert.h>

#include <ddslib/dllist.h>

#include "../riscos/wimp/op.h"

#include "../yacitros/desktop/wimpmsg.h"
#include "../yacitros/desktop/task.h"

#include "../utils.h"
#include "throw.h"

#undef STEP
#define STEP 16u

/* Each chunk covers from ['limit'-'STEP'..'limit'). */
struct chunk {
  dllist_elem(struct chunk) others;
  wimp_msgtype limit;
  int count[STEP];
  unsigned long sum;
};

static dllist_hdr(struct chunk) wimpmsg_list;

static void wimpmsg_strip(void)
{
  struct chunk *found, *celem;

  for (found = dllist_first(&wimpmsg_list); found; found = celem) {
    celem = dllist_next(others, found);
    if (found->sum == 0) {
      dllist_unlink(&wimpmsg_list, others, found);
      free(found);
    }
  }
}

int wimpmsg_getlevel(wimp_msgtype mt)
{
  struct chunk *found;

  for (found = dllist_first(&wimpmsg_list); found && mt >= found->limit;
       found = dllist_next(others, found))
    ;
  if (!found || mt < found->limit - STEP)
    return 0;
  return found->count[mt + STEP - found->limit];
}

static int wimpmsg_ensure(const wimp_msgtype *arr)
{
  struct chunk *found, *celem;
  const wimp_msgtype *curr;

  /* Ensure that we can allocate memory for all the chunks. */
  for (curr = arr; *curr; curr++) {
    for (found = dllist_first(&wimpmsg_list); found && *curr >= found->limit;
         found = dllist_next(others, found))
      ;
    if (found && *curr >= found->limit - STEP)
      continue; /* The chunk already exists. */

    /* Create a new chunk. */
    ALLOCATE(celem);
    if (!celem) {
      /* Can't do all of them.  Go through the list removing empty
         chunks, which we probably just created. */
      wimpmsg_strip();

      /* Report failure. */
      return -2;
    }

    /* Okay - initialise the new chunk. */
    celem->limit = *curr + STEP - *curr % STEP;
    celem->sum = 0;
    for (size_t offset = 0; offset < STEP; offset++)
      celem->count[offset] = 0;
    dllist_insertbefore(&wimpmsg_list, others, found, celem);
  }

  /* At this point, we definitely have enough memory to account for
     all the messages, so they can be changed atomically. */
  return 0;
}

int wimpmsg_accept(wimp_msgtype *arr)
{
  struct chunk *found;
  wimp_msgtype *build = arr, *curr;

  if (wimpmsg_ensure(arr))
    return -2;

  for (curr = arr; *curr; curr++) {
    for (found = dllist_first(&wimpmsg_list); found && *curr >= found->limit;
         found = dllist_next(others, found))
      ;
    assert(found && *curr >= found->limit - STEP);
    if (!found->count[*curr + STEP - found->limit]++)
      *(build++) = *curr;

    /* If we've incremented a negative number, the absolute count must
       go down; up otherwise. */
    if (found->count[*curr + STEP - found->limit] < 1)
      found->sum--;
    else
      found->sum++;
  }
  *build = 0;
  THROW(wimp_addmessages(arr));

  return 0;
}

int wimpmsg_reject(wimp_msgtype *arr)
{
  struct chunk *found;
  wimp_msgtype *build = arr, *curr = arr;

  if (wimpmsg_ensure(arr))
    return -2;

  while (*curr) {
    for (found = dllist_first(&wimpmsg_list);
         found && *curr >= found->limit;
         found = dllist_next(others, found))
      ;
    if (found && *curr >= found->limit - STEP) {
      if (!--found->count[*curr + STEP - found->limit])
        *(build++) = *curr;

      /* If we've decremented a positive number, the absolute count must
         go down; up otherwise. */
      if (found->count[*curr + STEP - found->limit] > -1)
        found->sum--;
      else
        found->sum++;
    }
    curr++;
  }
  *build = 0;
  THROW(wimp_removemessages(arr));

  wimpmsg_strip();
  return 0;
}
