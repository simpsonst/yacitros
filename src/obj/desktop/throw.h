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

#ifndef Yacitros_desktop_throw
#define Yacitros_desktop_throw

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

#include "../yacitros/common.h"

  // Copied from task.h for convenience.
  Yacitros_USERESULT
  _kernel_oserror *task_err(void);

  // private - used by other desktop modules (win, menu, etc)
  _kernel_oserror *task_seterr(_kernel_oserror *);

#define THROW(V) do { \
  if (task_seterr(V)) return -1; \
} while (0)

#define THROWE(V) do { \
  if (task_seterr(V)) return event_CLAIM; \
} while (0)

#define THROWN(V) do { \
  if (task_seterr(V)) return NULL; \
} while (0)

#define THROWI(V) do { \
  if ((V) < 0) return -1; \
} while (0)

#define IGNORE(V) do { \
  _kernel_oserror *farty_temp = (V); \
  farty_temp = farty_temp; \
} while (0)

#define IGNOREI(V) do { \
  int farty_temp = (V); \
  farty_temp = farty_temp; \
} while (0)

#define STOP do { \
  task_seterr(NULL); \
  return -1; \
} while (0)

#ifdef __cplusplus
}
#endif

#endif
