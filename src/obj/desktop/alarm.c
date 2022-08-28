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

#include "../yacitros/desktop/alarm.h"



struct event_alarm_db_tag;

struct event_alarm_tag {
  dllist_elem(struct event_alarm_tag) others;
  os_monotime when;
  alarm_f *fn;
  void *ctxt;
  unsigned loc : 2;
};

static int event_alarm_processready(struct event_alarm_db_tag *dbp,
                                    const os_monotime *now)
{
  int n = 0;
  event_alarm_h ah = dllist_first(&dbp->ready);

  if (!ah) return 0;
  while (ah) {
    n++;
    dllist_unlink(&dbp->ready, others, ah);
    dllist_append(&dbp->done, others, ah);
    ah->loc = alarm_DONE;
    if (ah->fn) (*ah->fn)(ah->ctxt);
    ah = dllist_first(&dbp->ready);
  }
  return n;
}

static void event_alarm_makeready(struct event_alarm_db_tag *dbp,
                                  const os_monotime *now)
{
  event_alarm_h ah;

  while ((ah = dllist_first(&dbp->seq)) && *now - ah->when > 0) {
    dllist_unlink(&dbp->seq, others, ah);
    ah->loc = alarm_READY;
    dllist_append(&dbp->ready, others, ah);
  }
}

static void event_alarm_makereadyn(struct event_alarm_db_tag *dbp,
                                   const os_monotime *now, int n)
{
  event_alarm_h ah;

  while (n > 0 &&
         (ah = dllist_first(&dbp->seq)) && *now - ah->when > 0) {
    n--;
    dllist_unlink(&dbp->seq, others, ah);
    ah->loc = alarm_READY;
    dllist_append(&dbp->ready, others, ah);
  }
}

void event_alarm_init(struct event_alarm_db_tag *dbp)
{
  dllist_init(&dbp->seq);
  dllist_init(&dbp->ready);
  dllist_init(&dbp->done);
}

void event_alarm_term(struct event_alarm_db_tag *dbp)
{
  event_alarm_h ah;

  while ((ah = dllist_first(&dbp->seq)))
    event_alarm_cancel(dbp, ah);
  while ((ah = dllist_first(&dbp->ready)))
    event_alarm_cancel(dbp, ah);
  while ((ah = dllist_first(&dbp->done)))
    event_alarm_cancel(dbp, ah);
}

#define LESS_THAN(A,B) ((A) - (B) > ((~(os_monotime) 0) >> 1))

event_alarm_h event_alarm_set(struct event_alarm_db_tag *dbp,
                              const os_monotime *tv, alarm_f *f, void *c)
{
  event_alarm_h is, ah;

  ah = malloc(sizeof(struct event_alarm_tag));
  if (!ah) return NULL;

  ah->when = *tv;
  ah->fn = f;
  ah->ctxt = c;
  ah->loc = alarm_SEQ;

  is = dllist_last(&dbp->seq);

  while (is && LESS_THAN(ah->when, is->when))
    is = dllist_prev(others, is);

  dllist_insertafter(&dbp->seq, others, is, ah);

  return ah;
}

void event_alarm_cancel(struct event_alarm_db_tag *dbp, event_alarm_h ah)
{
  if (!ah) return;

  switch (ah->loc) {
  case alarm_SEQ:
    dllist_unlink(&dbp->seq, others, ah);
    break;
  case alarm_READY:
    dllist_unlink(&dbp->ready, others, ah);
    break;
  case alarm_DONE:
    dllist_unlink(&dbp->done, others, ah);
    break;
  }

  free(ah);
}

alarm_rc event_alarm_poll(struct event_alarm_db_tag *dbp,
                          const os_monotime *now, os_monotime *next)
{
  event_alarm_h af;

  af = dllist_first(&dbp->seq);
  if (!af) return alarm_OFF;

  if (!LESS_THAN(*now, af->when)) {
    *next = *now;
    return alarm_PENDING;
  }

  *next = af->when;
  return alarm_OK;
}

alarm_rc event_alarm_polldelay(struct event_alarm_db_tag *dbp,
                               const os_monotime *now, os_monotime *next)
{
  event_alarm_h af;

  af = dllist_first(&dbp->seq);
  if (!af) return alarm_OFF;

  if (!LESS_THAN(*now, af->when)) {
    *next = 0;
    return alarm_PENDING;
  }

  *next = af->when - *now;
  return alarm_OK;
}

int event_alarm_process(struct event_alarm_db_tag *dbp,
                        const os_monotime *now)
{
  event_alarm_makeready(dbp, now);
  return event_alarm_processready(dbp, now);
}

int event_alarm_processn(struct event_alarm_db_tag *dbp,
                         const os_monotime *now, int n)
{
  event_alarm_makereadyn(dbp, now, n);
  return event_alarm_processready(dbp, now);
}

event_alarm_db event_alarmdb;
