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

#include <assert.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>

#include "../riscos/wimp/op.h"
#include "../riscos/wimp/msgtypes.h"
#include "../riscos/wimp/event.h"
#include "../riscos/wimp/errflags.h"

#include "../yacitros/desktop/task.h"
#include "../yacitros/desktop/event.h"

#include "throw.h"

wimp_taskhandle task_handle = (wimp_taskhandle) 0;
const char *task_name = "no task";
event_ref task_quithandle;

static event_rspcode task_catchquit(void *quv, wimp_eventtype et, void *datav)
{
  int *qu = quv;
  wimp_msghdr *data = datav;

  if (et != wimp_User_Message && et != wimp_User_Message_Recorded)
    return event_SHIRK;
  if (data->action == 0) {
    *qu = true;
    return event_CLAIM;
  }
  return event_SHIRK;
}

int task_init(const char *name, int *qf)
{
  static wimp_msgtype zero = 0;

  if (task_isready()) return -1;
  task_handle = (wimp_taskhandle) 0;
  THROW(wimp_initialise(3.00, name, &task_handle, &zero));
  task_name = name;
  task_quithandle = event_setpre(&task_catchquit, qf);
  event_select((1<<wimp_User_Message) |
               (1<<wimp_User_Message_Recorded));
  return 0;
}

void task_term(void)
{
  if (!task_isready()) return;
  IGNORE(wimp_closedown(task_handle));
  task_handle = (wimp_taskhandle) 0;
  task_name = "no task";
  event_cancel(task_quithandle);
  event_deselect((1<<wimp_User_Message) |
                 (1<<wimp_User_Message_Recorded));
}

int task_isready(void) { return !!task_handle; }
wimp_taskhandle task_gethandle(void) { return task_handle; }
const char *task_getname(void) { return task_name; }

void task_error_va(int fatal, const char *fmt, va_list arg)
{
  wimp_errflags ef;
  _kernel_oserror em = { 255, "" };
  ef.word = wimp_EFOK;
  vsprintf(em.errmess, fmt, arg);
  wimp_reporterror(&em, ef, task_name);
  if (fatal) {
    task_term();
    exit(fatal);
  }
}

void task_error(int fatal, const char *fmt, ...)
{
  va_list arg;

  va_start(arg, fmt);
  task_error_va(fatal, fmt, arg);
  va_end(arg);
}

_kernel_oserror *task_complain(_kernel_oserror *e)
{
  if (e) {
    wimp_errflags ef;
    ef.word = wimp_EFOK;
    (void) wimp_reporterror(e, ef, task_name);
  }
  return e;
}

void task_assert(const char *x, const char *f, int n)
{
  if (task_isready()) {
    task_error(1, "Assertion failed in %s at line %d: %s", f, n, x);
  } else {
    fprintf(stderr, "Assertion failed in %s at line %d: %s\n", f, n, x);
    fflush(stderr);
    exit(1);
  }
}



static _kernel_oserror *lasterr;

_kernel_oserror *task_err(void)
{
  return lasterr;
}

_kernel_oserror *task_seterr(_kernel_oserror *e)
{
  return (lasterr = e);
}
