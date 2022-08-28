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

#ifndef Yacitros_os_var
#define Yacitros_os_var

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>

#include "types.h"

#include "../yacitros/common.h"

  enum {
    os_STRING,
    os_NUMBER,
    os_MACRO,
    os_EXPANDED,
    os_CODE = 16
  };

  typedef int os_vartype;

  Yacitros_USERESULT
  _kernel_oserror *os_getvarval(const char *match, void *, size_t *,
                                const char **index, os_vartype *);

  Yacitros_USERESULT
  _kernel_oserror *os_setvarval(const char *match, const void *, size_t,
                                const char **index, os_vartype *);

#ifdef __cplusplus
}
#endif

#endif
