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

#ifndef Yacitros_arm_cond
#define Yacitros_arm_cond

#ifdef __cplusplus
extern "C" {
#endif

#define arm_EQ 0x0 /* equal */
#define arm_NE 0x1 /* not equal */
#define arm_CS 0x2 /* varry set */
#define arm_CC 0x3 /* carry clear */
#define arm_MI 0x4 /* minus */
#define arm_PL 0x5 /* plus */
#define arm_VS 0x6 /* overflow set */
#define arm_VC 0x7 /* overflow clear */
#define arm_HI 0x8 /* higher */
#define arm_LS 0x9 /* lower or same */
#define arm_GE 0xa /* greater or equal */
#define arm_LT 0xb /* less */
#define arm_GT 0xc /* greater */
#define arm_LE 0xd /* less or equal */
#define arm_AL 0xe /* always */
#define arm_NV 0xf /* never */

#ifdef __cplusplus
}
#endif

#endif
