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

#ifndef Yacitros_arm_format
#define Yacitros_arm_format

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
  unsigned Rop2 : 4, S2: 8, Rd : 4, Rn : 4, S : 1,
    OpCode : 4, I : 1, Id : 2, Cond : 4;
} arm_alureg;

typedef struct {
  unsigned Iop2 : 8, S2 : 4, Rd : 4, Rn : 4, S : 1,
    OpCode : 4, I : 1, Id : 2, Cond : 4;
} arm_aluimm;

typedef struct {
  signed offset : 24;
  unsigned L : 1, Id : 3, Cond : 4;
} arm_branch;

typedef struct {
  unsigned Rm : 4, Ida : 4, Rs : 4, Rd : 4,
    Rn : 4, S : 1, A : 1, Idb : 6, Cond : 4;
} arm_xply;

typedef struct {
  signed offset : 12;
  unsigned Rd : 4, Rn : 4, L : 1, W : 1, B : 1,
    U : 1, P : 1, I : 1, Id : 2, Cond : 4;
} arm_mem1;

typedef struct {
  unsigned R0 : 1, R1 : 1, R2 : 1, R3 : 1, R4 : 1, R5 : 1, R6 : 1, R7 : 1;
  unsigned R8 : 1, R9 : 1, R10 : 1, R11 : 1, R12 : 1, R13 : 1, R14 : 1, R15 : 1;
  unsigned Rn : 4, L : 1, W : 1, S : 1, U : 1, P : 1, Id : 3, Cond : 4;
} arm_memx;

typedef struct {
  unsigned comment : 24, Id : 4, Cond : 4;
} arm_swi;

typedef union {
  uint32_t word;
  arm_alureg alureg;
  arm_aluimm aluimm;
  arm_branch branch;
  arm_xply xply;
  arm_mem1 mem1;
  arm_memx memx;
  arm_swi swi;
} arm_inst;

#ifdef __cplusplus
}
#endif

#endif
