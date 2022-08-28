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

#ifndef Yacitros_arm_mnemonic
#define Yacitros_arm_mnemonic

#ifdef __cplusplus
extern "C" {
#endif

#define arm_AND 0x0 /* bitwise AND */
#define arm_EOR 0x1 /* bitwise exclusive-OR */
#define arm_SUB 0x2 /* subtract */
#define arm_RSB 0x3 /* reverse subtract */
#define arm_ADD 0x4 /* add */
#define arm_ADC 0x5 /* add with carry */
#define arm_SBC 0x6 /* subtract with carry */
#define arm_RSC 0x7 /* reverse subtract with carry */
#define arm_TST 0x8 /* test bits */
#define arm_TEQ 0x9 /* test equivalence */
#define arm_CMP 0xa /* compare */
#define arm_CMN 0xb /* compare negative */
#define arm_ORR 0xc /* bitwise inclusive-OR */
#define arm_MOV 0xd /* move */
#define arm_BIC 0xe /* bit clear */
#define arm_MVN 0xf /* move not */

#ifdef __cplusplus
}
#endif

#endif
