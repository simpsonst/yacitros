// -*- c-basic-offset: 2; indent-tabs-mode: nil -*-

/*
  Yacitros: Yet Another C Interface to RISC OS
  Copyright (C) 2007 Steven Simpson

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

#ifndef Yacitros_yacitros_common
#define Yacitros_yacitros_common

#if __GNUC__ >= 3
#define Yacitros_deprecated(D) __attribute__ ((deprecated)) D
#else
#define Yactiros_deprecated(D) D
#endif


#if __GNUC__ >= 3
#define Yacitros_USERESULT __attribute__ ((warn_unused_result))
#else
#define Yacitros_USERESULT
#endif

#endif
