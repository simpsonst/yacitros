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

#include "../riscos/wimp/msgtypes.h"

#include "../yacitros/desktop/help.h"

int help_delimitmsg(help_msgblock *b)
{
  const char *c;

  switch (b->hdr.action) {
  case wimp_Message_HelpRequest:
    b->hdr.size = 40;
    return 0;
  case wimp_Message_HelpReply:
    b->hdr.size = 23;
    c = b->body.rep.text;
    while (++b->hdr.size < 259 && *c++ != '\0')
      ;
    b->hdr.size &= ~3;
    return 0;
  default:
    return -1;
  }
}
