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

#ifndef Yacitros_file_object
#define Yacitros_file_object

#ifdef __cplusplus
extern "C" {
#endif


#include "../types.h"
#include "types.h"

#include "../../yacitros/common.h"

  Yacitros_USERESULT
  _kernel_oserror *file_save(const char *, void *, size_t, void *, void *);
  Yacitros_USERESULT
  _kernel_oserror *file_savetyped(const char *, void *, size_t, file_type);
  Yacitros_USERESULT
  _kernel_oserror *file_load(const char *, void *,
                             struct file_catinfo *, file_kind *);
  Yacitros_USERESULT
  _kernel_oserror *file_load_fp(const char *, void *,
                                struct file_catinfo *, file_kind *);
  Yacitros_USERESULT
  _kernel_oserror *file_load_up(const char *, void *, const char *,
                                struct file_catinfo *, file_kind *);
  Yacitros_USERESULT
  _kernel_oserror *file_load_vp(const char *, void *, const char *,
                                struct file_catinfo *, file_kind *);
  Yacitros_USERESULT
  _kernel_oserror *file_createdir(const char *, int);
  Yacitros_USERESULT
  _kernel_oserror *file_create(const char *, size_t, void *, void *);
  Yacitros_USERESULT
  _kernel_oserror *file_createtyped(const char *, size_t, file_type);
  Yacitros_USERESULT
  _kernel_oserror *file_delete(const char *,
                               struct file_catinfo *, file_kind *);
  Yacitros_USERESULT
  _kernel_oserror *file_getcat(const char *,
                               struct file_catinfo *, file_kind *);
  Yacitros_USERESULT
  _kernel_oserror *file_getcat_fp(const char *,
                                  struct file_catinfo *, file_kind *);
  Yacitros_USERESULT
  _kernel_oserror *file_getcat_up(const char *, const char *,
                                  struct file_catinfo *, file_kind *);
  Yacitros_USERESULT
  _kernel_oserror *file_getcat_vp(const char *, const char *,
                                  struct file_catinfo *, file_kind *);
  Yacitros_USERESULT
  _kernel_oserror *file_setcat(const char *, struct file_catinfo *);
  Yacitros_USERESULT
  _kernel_oserror *file_setload(const char *, void *);
  Yacitros_USERESULT
  _kernel_oserror *file_setexec(const char *, void *);
  Yacitros_USERESULT
  _kernel_oserror *file_settype(const char *, file_type);
  Yacitros_USERESULT
  _kernel_oserror *file_setattr(const char *, file_attr);
  Yacitros_USERESULT
  _kernel_oserror *file_stamp(const char *);
  Yacitros_USERESULT
  _kernel_oserror *file_makeerror(const char *, file_kind);

#ifdef __cplusplus
}
#endif

#endif
