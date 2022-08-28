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

#include "../riscos/in.h"

uint_fast32_t ntohu32(uint_fast32_t i)
  { return i << 24 & 0xff000000 |
           i << 8 & 0xff0000 |
           i >> 8 & 0xff00 |
           i >> 24 & 0xff; }

uint_fast16_t ntohu16(uint_fast16_t i)
  { return i << 8 & 0xff00 |
           i >> 8 & 0xff; }

#ifdef __GNUC__
uint_fast64_t ntohu64(uint_fast64_t i)
  { return i << 56 & 0xff00000000000000 |
           i << 40 & 0xff000000000000 |
           i << 24 & 0xff0000000000 |
           i << 8 & 0xff00000000 |
           i >> 8 & 0xff000000 |
           i >> 24 & 0xff0000 |
           i >> 40 & 0xff00 |
           i >> 56 & 0xff; }
#endif
