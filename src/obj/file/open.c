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

#include "../riscos/file/open.h"

_kernel_oserror *file_geteof(file_handle fh, int *f)
{
  return _swix(XOS_Args, _INR(0,1)|_OUT(2), 5, fh, f);
}

_kernel_oserror *file_getext(file_handle fh, size_t *s)
{
  return _swix(XOS_Args, _INR(0,1)|_OUT(2), 2, fh, s);
}

_kernel_oserror *file_setext(file_handle fh, size_t s)
{
  return _swix(XOS_Args, _INR(0,2), 3, fh, s);
}

_kernel_oserror *file_getptr(file_handle fh, size_t *p)
{
  return _swix(XOS_Args, _INR(0,1)|_OUT(2), 0, fh, p);
}

_kernel_oserror *file_setptr(file_handle fh, size_t p)
{
  return _swix(XOS_Args, _INR(0,2), 1, fh, p);
}

_kernel_oserror *file_getmax(file_handle fh, size_t *m)
{
  return _swix(XOS_Args, _INR(0,1)|_OUT(2), 4, fh, m);
}

_kernel_oserror *file_setmax(file_handle fh, size_t m)
{
  return _swix(XOS_Args, _INR(0,2), 6, fh, m);
}

_kernel_oserror *file_getflags(file_handle fh, unsigned *f)
{
  return _swix(XOS_Args, _INR(0,1)|_OUT(2), 254, fh, f);
}

_kernel_oserror *file_flush(file_handle fh)
{
  return _swix(XOS_Args, _INR(0,1), 255, fh);
}

_kernel_oserror *file_getbyte(file_handle fh, char *c)
{
  return _swix(XOS_BGet, _IN(1)|_OUT(0), fh, c);
}

_kernel_oserror *file_putbyte(file_handle fh, char c)
{
  return _swix(XOS_BPut, _INR(0,1), c, fh);
}

_kernel_oserror *file_getblock(file_handle fh, void *b, size_t *s)
{
#if __GNUC__ > 1 && !__STRICT_ANSI__
#warning "Useless API"
#endif
  _kernel_oserror *ep;
  int tmp;
  ep = _swix(XOS_GBPB, _INR(0,3)|_OUT(3), 4, fh, b, *s, &tmp);
  *s -= tmp;
  return ep;
}

_kernel_oserror *file_getblockfrom(file_handle fh,
                                   void *b, size_t *s, size_t p)
{
#if __GNUC__ > 1 && !__STRICT_ANSI__
#warning "Useless API"
#endif
  _kernel_oserror *ep;
  int tmp;
  ep = _swix(XOS_GBPB, _INR(0,4)|_OUT(3), 3, fh, b, *s, p, &tmp);
  *s -= tmp;
  return ep;
}

_kernel_oserror *file_putblock(file_handle fh, const void *b, size_t *s)
{
#if __GNUC__ > 1 && !__STRICT_ANSI__
#warning "Useless API"
#endif
  _kernel_oserror *ep;
  int tmp;
  ep = _swix(XOS_GBPB, _INR(0,3)|_OUT(3), 2, fh, b, *s, &tmp);
  *s -= tmp;
  return ep;
}

_kernel_oserror *file_putblockfrom(file_handle fh, const void *b,
                                   size_t *s, size_t p)
{
#if __GNUC__ > 1 && !__STRICT_ANSI__
#warning "Useless API"
#endif
  _kernel_oserror *ep;
  int tmp;
  ep = _swix(XOS_GBPB, _INR(0,4)|_OUT(3), 1, fh, b, *s, p, &tmp);
  *s -= tmp;
  return ep;
}
