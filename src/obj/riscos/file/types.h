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

#ifndef Yacitros_file_types
#define Yacitros_file_types

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>
#include <stdint.h>

#include "../types.h"

#include "../../yacitros/common.h"

  typedef uint8_t file_handle;
  Yacitros_deprecated(typedef file_handle file_t);

  typedef int32_t file_type;
  Yacitros_deprecated(typedef file_type file_type_t);

  typedef uint32_t file_attr;
  Yacitros_deprecated(typedef file_attr file_attr_t);

  typedef enum {
    file_NOTFOUND = 0,
    file_FILE,
    file_DIR,
    file_IMAGE
  } file_kind;
  Yacitros_deprecated(typedef file_kind file_kind_t);

  struct file_catinfo {
    void *load, *exec;
    size_t length;
    file_attr attr;
  };

  struct file_dirent {
    void *load, *exec;
    size_t length;
    file_attr attr;
    file_kind kind;
    char name[1];
  };

  struct file_dirlent {
    void *load, *exec;
    size_t length;
    file_attr attr;
    file_kind kind;
    uint32_t sysint;
    char name[1];
  };

#ifdef __cplusplus
}
#endif

#endif
