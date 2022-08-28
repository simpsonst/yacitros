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

#ifndef Yacitros_file_handle
#define Yacitros_file_handle

#ifdef __cplusplus
extern "C" {
#endif


#include "../types.h"
#include "types.h"

#include "../../yacitros/common.h"

  Yacitros_USERESULT
  _kernel_oserror *file_close(file_handle fh);
  Yacitros_USERESULT
  _kernel_oserror *file_open(file_handle *fh, const char *n,
                             unsigned mode, const char *p);

#define file_EX 0x40 /* don't create new file */
#define file_RW 0x80 /* open for read/write (read-only is default) */
#define file_NE 0x08 /* raise error if file_EX and file not found;
                        default: *fh = 0 */
#define file_DE 0x04 /* raise error on opening a directory */
#define file_FP 0x00 /* search in File$Path */
#define file_UP 0x01 /* search path in string */
#define file_VP 0x02 /* search path in system variable */
#define file_NP 0x03 /* no search path */

#define file_READONLY (file_EX|file_NP)
#define file_CREATE (file_RW|file_DE|file_NP)
#define file_UPDATE (file_RW|file_EX|file_NP)

#ifdef __cplusplus
}
#endif

#endif
