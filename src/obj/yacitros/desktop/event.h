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

#ifndef Yacitros_desktop_event
#define Yacitros_desktop_event

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

#include "../../riscos/wimp/types.h"

#include "types.h"
#include "alarm.h"

#include "../common.h"

  /* Registration */
  event_ref event_setpre(event_proc *func, void *handle)
       Yacitros_USERESULT;
  event_ref event_setpost(event_proc *func, void *handle)
       Yacitros_USERESULT;
  event_ref event_setafter(event_proc *func, void *h, event_ref)
       Yacitros_USERESULT;
  event_ref event_setbefore(event_proc *func, void *h, event_ref)
       Yacitros_USERESULT;
  void event_cancel(event_ref);

  event_idlerref event_setidler(event_idlerproc *, void *h)
       Yacitros_USERESULT;
  void event_cancelidler(event_idlerref);

  void event_select(wimp_eventmask);
  void event_deselect(wimp_eventmask);

  /* Submit an event to the handlers. */
  event_rspcode event_fake(wimp_eventtype, void *data);

  /* Process one event including alarms. */
  Yacitros_USERESULT
  int event_process(void);

#define event_setalarm(T,F,V) event_alarm_set(&event_alarmdb, (T), (F), (V))
#define event_cancelalarm(H) event_alarm_cancel(H)

  extern event_alarm_db event_alarmdb;

#ifdef __cplusplus
}
#endif

#endif
