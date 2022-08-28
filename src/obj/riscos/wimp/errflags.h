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

#ifndef Yacitros_wimp_errflags
#define Yacitros_wimp_errflags

#ifdef __cplusplus
extern "C" {
#endif


#define wimp_EFOK         1
#define wimp_EFCANCEL     2
#define wimp_EFHICANCEL   4
#define wimp_EFNOPROMPT   8
#define wimp_EFNOPREFIX  16
#define wimp_EFIMMEDIATE 32
#define wimp_EFSELECT    64

#ifdef __cplusplus
}
#endif

#endif
