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

#include <kernel.h>
#include <swis.h>

#include <riscos/swi/OS.h>

#include "../riscos/file/object.h"

_kernel_oserror *file_save(const char *n, void *a, size_t s, void *r, void *x)
{
  return _swix(XOS_File, _INR(0,5), 0, n, r, x, a, s);
}

_kernel_oserror *file_savetyped(const char *n, void *a,
                                size_t s, file_type t)
{
  return _swix(XOS_File, _INR(0,2)|_INR(4,5), 10, n, t, a, s);
}

_kernel_oserror *file_load(const char *n, void *a,
                           struct file_catinfo *c, file_kind *k)
{
  int tmp;
  return _swix(XOS_File, _INR(0,3)|_OUT(0)|_OUTR(2,5), 16, n, a, 0,
               k?(int*)k:&tmp, c?(int*)&c->load:&tmp, c?(int*)&c->exec:&tmp,
               c?(int*)&c->length:&tmp, c?(int*)&c->attr:&tmp);
}

_kernel_oserror *file_load_fp(const char *n, void *a,
                              struct file_catinfo *c, file_kind *k)
{
  int tmp;
  return _swix(XOS_File, _INR(0,3)|_OUT(0)|_OUTR(2,5), 255, n, a, 0,
               k?(int*)k:&tmp, c?(int*)&c->load:&tmp, c?(int*)&c->exec:&tmp,
               c?(int*)&c->length:&tmp, c?(int*)&c->attr:&tmp);
}

_kernel_oserror *file_load_up(const char *n, void *a, const char *p,
                              struct file_catinfo *c, file_kind *k)
{
  int tmp;
  return _swix(XOS_File, _INR(0,4)|_OUT(0)|_OUTR(2,5), 12, n, a, 0, p,
               k?(int*)k:&tmp, c?(int*)&c->load:&tmp, c?(int*)&c->exec:&tmp,
               c?(int*)&c->length:&tmp, c?(int*)&c->attr:&tmp);
}

_kernel_oserror *file_load_vp(const char *n, void *a, const char *p,
                              struct file_catinfo *c, file_kind *k)
{
  int tmp;
  return _swix(XOS_File, _INR(0,4)|_OUT(0)|_OUTR(2,5), 14, n, a, 0, p,
               k?(int*)k:&tmp, c?(int*)&c->load:&tmp, c?(int*)&c->exec:&tmp,
               c?(int*)&c->length:&tmp, c?(int*)&c->attr:&tmp);
}

_kernel_oserror *file_createdir(const char *n, int e)
{
  return _swix(XOS_File, _INR(0,2), 8, n, e);
}

_kernel_oserror *file_create(const char *n, size_t s, void *r, void *x)
{
  return _swix(XOS_File, _INR(0,5), 7, n, r, x, 0, s);
}

_kernel_oserror *file_createtyped(const char *n, size_t s, file_type t)
{
  return _swix(XOS_File, _INR(0,2)|_INR(4,5), 11, n, t, 0, s);
}

_kernel_oserror *file_delete(const char *n,
                             struct file_catinfo *c, file_kind *k)
{
  int tmp;
  return _swix(XOS_File, _INR(0,1)|_OUT(0)|_OUTR(2,5), 6, n,
               k?(int*)k:&tmp, c?(int*)&c->load:&tmp, c?(int*)&c->exec:&tmp,
               c?(int*)&c->length:&tmp, c?(int*)&c->attr:&tmp);
}

_kernel_oserror *file_getcat(const char *n,
                             struct file_catinfo *c, file_kind *k)
{
  int tmp;
  return _swix(XOS_File, _INR(0,1)|_OUT(0)|_OUTR(2,5), 17, n,
               k?(int*)k:&tmp, c?(int*)&c->load:&tmp, c?(int*)&c->exec:&tmp,
               c?(int*)&c->length:&tmp, c?(int*)&c->attr:&tmp);
}

_kernel_oserror *file_getcat_fp(const char *n,
                                struct file_catinfo *c, file_kind *k)
{
  int tmp;
  return _swix(XOS_File, _INR(0,1)|_OUT(0)|_OUTR(2,5), 5, n,
               k?(int*)k:&tmp, c?(int*)&c->load:&tmp, c?(int*)&c->exec:&tmp,
               c?(int*)&c->length:&tmp, c?(int*)&c->attr:&tmp);
}

_kernel_oserror *file_getcat_up(const char *n, const char *p,
                                struct file_catinfo *c, file_kind *k)
{
  int tmp;
  return _swix(XOS_File, _INR(0,1)|_IN(4)|_OUT(0)|_OUTR(2,5), 13, n, p,
               k?(int*)k:&tmp, c?(int*)&c->load:&tmp, c?(int*)&c->exec:&tmp,
               c?(int*)&c->length:&tmp, c?(int*)&c->attr:&tmp);
}

_kernel_oserror *file_getcat_vp(const char *n, const char *p,
                                struct file_catinfo *c, file_kind *k)
{
  int tmp;
  return _swix(XOS_File, _INR(0,1)|_IN(4)|_OUT(0)|_OUTR(2,5), 15, n, p,
               k?(int*)k:&tmp, c?(int*)&c->load:&tmp, c?(int*)&c->exec:&tmp,
               c?(int*)&c->length:&tmp, c?(int*)&c->attr:&tmp);
}

_kernel_oserror *file_setcat(const char *n, struct file_catinfo *c)
{
  return _swix(XOS_File, _INR(0,3)|_IN(5), 1, n, c->load, c->exec, c->attr);
}

_kernel_oserror *file_setload(const char *n, void *r)
{
  return _swix(XOS_File, _INR(0,2), 2, n, r);
}

_kernel_oserror *file_setexec(const char *n, void *x)
{
  return _swix(XOS_File, _INR(0,1)|_IN(3), 3, n, x);
}

_kernel_oserror *file_settype(const char *n, file_type t)
{
  return _swix(XOS_File, _INR(0,2), 18, n, t);
}

_kernel_oserror *file_setattr(const char *n, file_attr a)
{
  return _swix(XOS_File, _INR(0,1)|_IN(5), 4, n, a);
}

_kernel_oserror *file_stamp(const char *n)
{
  return _swix(XOS_File, _INR(0,1), 9, n);
}

_kernel_oserror *file_makeerror(const char *n, file_kind k)
{
  return _swix(XOS_File, _INR(0,2), 19, n, k);
}
