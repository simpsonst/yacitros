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

#ifndef Yacitros_desktop_alarm
#define Yacitros_desktop_alarm

#ifdef __cplusplus
extern "C" {
#endif

#include <ddslib/dllist.h>

#include "../../riscos/types.h"

#include "../common.h"

  typedef enum {
    alarm_OFF = -1,
    alarm_OK = 0,
    alarm_PENDING = 1,
    alarm_ERROR = 2
  } alarm_rc;

  enum { alarm_SEQ, alarm_READY, alarm_DONE };

  typedef void alarm_f(void *);

  typedef struct event_alarm_tag *event_alarm_h;

  typedef struct event_alarm_db_tag {
    dllist_hdr(struct event_alarm_tag) seq, ready, done;
  } event_alarm_db;

  void event_alarm_init(event_alarm_db *);
  void event_alarm_term(event_alarm_db *);
  alarm_rc event_alarm_poll(event_alarm_db *,
                            const os_monotime *now,
                            os_monotime *next);
  alarm_rc event_alarm_polldelay(event_alarm_db *,
                                 const os_monotime *now,
                                 os_monotime *delay);
  int event_alarm_process(event_alarm_db *,
                          const os_monotime *now);
  int event_alarm_processn(event_alarm_db *,
                           const os_monotime *now, int n);
  event_alarm_h event_alarm_set(event_alarm_db *,
                                const os_monotime *, alarm_f *, void *);
  void event_alarm_cancel(event_alarm_db *, event_alarm_h);

#ifdef __cplusplus
}
#endif

#endif
