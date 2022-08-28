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

#include <kernel.h>

#include <ddslib/dllist.h>

#include "../riscos/time.h"
#include "../riscos/wimp/op.h"
#include "../riscos/wimp/event.h"

#include "../yacitros/desktop/event.h"
#include "../yacitros/desktop/alarm.h"
#include "../yacitros/desktop/task.h"

#include "throw.h"

struct event_idler {
  dllist_elem(struct event_idler) others;
  event_idlerproc *func;
  void *handle;
};

struct event_procstr {
  dllist_elem(struct event_procstr) others;
  event_proc *func;
  void *handle;
};

dllist_loophdr(struct event_idler) event_idler_next;
dllist_hdr(struct event_procstr) event_dllist;
event_ref event_next;
wimp_eventmask event_mask = 0xe1831u;
int event_count[20] = {
  0, 1, 1, 1,
  0, 0, 1, 1,
  1, 1, 1, 0,
  0, 1, 1, 1,
  1, 0, 0, 0
};

/* Registration */
event_ref event_setpre(event_proc *func, void *h)
{ return event_setbefore(func, h, dllist_first(&event_dllist)); }

event_ref event_setpost(event_proc *func, void *h)
{ return event_setafter(func, h, dllist_last(&event_dllist)); }

event_ref event_setafter(event_proc *func, void *h, event_ref p)
{ return event_setbefore(func, h, p ? dllist_next(others, p) :
                         dllist_first(&event_dllist)); }

event_ref event_setbefore(event_proc *func,
                        void *h, event_ref p)
{
  struct event_procstr *r;
  if (!func) return NULL;
  r = malloc(sizeof *r);
  if (!r) return NULL;
  r->func = func;
  r->handle = h;
  dllist_insertbefore(&event_dllist, others, p, r);
  if (p == event_next)
    event_next = r;
  return r;
}

void event_cancel(event_ref p)
{
  if (!p) return;
  if (event_next == p)
    event_next = dllist_next(others, p);
  dllist_unlink(&event_dllist, others, p);
  free(p);
}

event_idlerref event_setidler(event_idlerproc *func, void *h)
{
  struct event_idler *r = malloc(sizeof *r);
  if (!r) return NULL;
  r->func = func;
  r->handle = h;
  dllist_loopinsertrel(&event_idler_next, others, r, before);
  return r;
}

void event_cancelidler(event_idlerref p)
{
  if (!p) return;
  if (dllist_loopentry(&event_idler_next) == p)
    dllist_loopentry(&event_idler_next) = dllist_next(others, p);
  dllist_loopunlink(&event_idler_next, others, p);
  free(p);
}

void event_select(wimp_eventmask em)
{
  wimp_eventtype et;
  wimp_eventmask bit = 1;
  int *cp = event_count;

#if 1
  for (et = 0; et < 20; et++, cp++, em >>= 1, bit <<= 1)
    if (em & 1)
      if ((*cp)++ == 0)
        event_mask &= ~bit;
#else
  /* em & em - 1 might be faster for this */
#endif
}

void event_deselect(wimp_eventmask em)
{
  wimp_eventtype et;
  wimp_eventmask bit = 1;
  int *cp = event_count;

  for (et = 0; et < 20; et++, cp++, em = (em>>1), bit = (bit<<1))
    if (em & 1)
      if (--(*cp) == 0)
        event_mask |= bit;
}

/* Submit an event to the handlers */
event_rspcode event_fake(wimp_eventtype etype, void *data)
{
  event_ref ep = event_next;
  int rsp = event_SHIRK;

  while (ep && rsp != event_CLAIM) {
    event_next = dllist_next(others, ep);
    rsp = (*ep->func)(ep->handle, etype, data);
    ep = event_next;
  }
  event_next = dllist_first(&event_dllist);
  return rsp;
}

static _kernel_oserror *event_poll(wimp_eventmask m,
                                   void *b, wimp_eventtype *et,
                                   os_monotime *tout)
{
  if (tout)
    return wimp_pollidle(m, b, et, *tout);
  return wimp_poll(m, b, et);
}

static void event_idler_process(void)
{
  struct event_idler *n = dllist_loopentry(&event_idler_next);

  dllist_loopinc(&event_idler_next, others, next);
  (*n->func)(n->handle);
}

int event_process(void)
{
  uint8_t block[256];
  wimp_eventtype et;
  os_monotime callback, *timeout = &callback, nowtime;
  wimp_eventmask em = event_mask;
  alarm_rc arc;

  THROW(os_readmonotonictime(&nowtime));

  if (!dllist_loopisempty(&event_idler_next)) {
    em &= ~(1<<wimp_Null_Reason_Code);
    timeout = NULL;
  } else if ((arc = event_alarm_poll(&event_alarmdb,
                                     &nowtime, timeout)) == alarm_OFF) {
    timeout = NULL;
  } else {
    em &= ~(1<<wimp_Null_Reason_Code);
  }

  THROW(event_poll(em, block, &et, timeout));

  task_seterr(NULL);
  event_fake(et, block);
  if (task_err()) return -1;

  if (et == wimp_Null_Reason_Code)
    if (!event_alarm_process(&event_alarmdb, &nowtime)
        && !dllist_loopisempty(&event_idler_next))
      event_idler_process();
  if (task_err()) return -1;
  return 0;
}
