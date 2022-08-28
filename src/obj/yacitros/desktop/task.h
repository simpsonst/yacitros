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

#ifndef Yacitros_desktop_task
#define Yacitros_desktop_task

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#include <kernel.h>

#include "../../riscos/wimp/types.h"

  int task_init(const char *name, int *qf);
  void task_term(void);

  int task_isready(void);
  wimp_taskhandle task_gethandle(void);
  const char *task_getname(void);
  void task_error(int fatal, const char *fmt, ...);
  void task_error_va(int fatal, const char *fmt, va_list arg);
  _kernel_oserror *task_complain(_kernel_oserror *e);

  void task_assert(const char *, const char *, int);

  Yacitros_USERESULT
  _kernel_oserror *task_err(void);

#ifndef NDEBUG
#ifdef assert
#undef assert
#define assert(X) \
if (!(X)) { \
  task_assert(#X, __FILE__, __LINE__); \
} else ;
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
