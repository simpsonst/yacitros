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

#ifndef Yacitros_vdu_modevars
#define Yacitros_vdu_modevars

#ifdef __cplusplus
extern "C" {
#endif


#define vdu_ModeFlags    0
#define vdu_ScrRCol      1
#define vdu_ScrBRow      2
#define vdu_NColour      3
#define vdu_XEigFactor   4
#define vdu_YEigFactor   5
#define vdu_LineLength   6
#define vdu_ScreenSize   7
#define vdu_YShftFactor  8
#define vdu_Log2BPP      9
#define vdu_Log2BPC     10
#define vdu_XWindLimit  11
#define vdu_YWindLimit  12

#ifdef __cplusplus
}
#endif

#endif
