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

#include <riscos/swi/Wimp.h>

#include "../riscos/wimp/op.h"

wimp_errrsp wimp_reporterror(const _kernel_oserror *e,
                            wimp_errflags f, const char *s)
{
  return (wimp_errrsp) _swi(Wimp_ReportError,
                            _INR(0,2)|_RETURN(1), e, f.word, s);
}

_kernel_oserror *wimp_preparecommandwindow(const char *title)
{
  return _swix(XWimp_CommandWindow, _IN(0), title);
}

_kernel_oserror *wimp_endcommandwindow(void)
{
  return _swix(XWimp_CommandWindow, _IN(0), 0);
}

_kernel_oserror *wimp_abortcommandwindow(void)
{
  return _swix(XWimp_CommandWindow, _IN(0), -1);
}
