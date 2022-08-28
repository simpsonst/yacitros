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

#ifndef Yacitros_desktop_wimpmsg
#define Yacitros_desktop_wimpmsg

#ifdef __cplusplus
extern "C" {
#endif

#include "../../riscos/wimp/types.h"

#include "../../yacitros/common.h"

  /* The argument must be a modifiable, 0-terminated array of message
     types.  It is changed to show which messages were actually
     enabled/disabled.  A negative value is returned on error (-2 =>
     internal error, e.g. out of memory; -1 => kernel error). */

  int wimpmsg_accept(wimp_msgtype *);
  int wimpmsg_reject(wimp_msgtype *);

  /* Get the current level (which may be negative).  Any positive
     value means the message type is enabled. */
  int wimpmsg_getlevel(wimp_msgtype);

#ifdef __cplusplus
}
#endif

#endif
