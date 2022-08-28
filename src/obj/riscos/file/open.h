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

#ifndef Yacitros_file_open
#define Yacitros_file_open

#ifdef __cplusplus
extern "C" {
#endif


#include <kernel.h>

#include "types.h"

#include "../../yacitros/common.h"

  Yacitros_USERESULT
  _kernel_oserror *file_geteof(file_handle, int *);
  Yacitros_USERESULT
  _kernel_oserror *file_getext(file_handle, size_t *);
  Yacitros_USERESULT
  _kernel_oserror *file_setext(file_handle, size_t);
  Yacitros_USERESULT
  _kernel_oserror *file_getptr(file_handle, size_t *);
  Yacitros_USERESULT
  _kernel_oserror *file_setptr(file_handle, size_t);
  Yacitros_USERESULT
  _kernel_oserror *file_getmax(file_handle, size_t *);
  Yacitros_USERESULT
  _kernel_oserror *file_setmax(file_handle, size_t);
  Yacitros_USERESULT
  _kernel_oserror *file_getflags(file_handle, unsigned *);
  Yacitros_USERESULT
  _kernel_oserror *file_flush(file_handle);
  Yacitros_USERESULT
  _kernel_oserror *file_getbyte(file_handle, char *);
  Yacitros_USERESULT
  _kernel_oserror *file_putbyte(file_handle, char);
  Yacitros_USERESULT
  _kernel_oserror *file_getblock(file_handle, void *, size_t *);
  Yacitros_USERESULT
  _kernel_oserror *file_getblockfrom(file_handle, void *, size_t *, size_t);
  Yacitros_USERESULT
  _kernel_oserror *file_putblock(file_handle, const void *, size_t *);
  Yacitros_USERESULT
  _kernel_oserror *file_putblockfrom(file_handle,
                                     const void *, size_t *, size_t);

#ifdef __cplusplus
}
#endif

#endif
