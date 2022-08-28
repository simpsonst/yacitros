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

#ifndef Yacitros_riscos_in
#define Yacitros_riscos_in

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>
#include <stdint.h>

struct in_addr {
  union {
    uint32_t word;
    uint8_t byte[4];
  } value;
};

struct sockaddr_in {
#ifdef __EASYC
  unsigned sin_family : 16, sin_port : 16;
#elif defined(__CC_NORCROFT) || defined(__GNUC__) || defined(__LCC__)
  uint16_t sin_family;
  uint16_t sin_port;
#else
#error Unknown compiler
#endif
  struct in_addr sin_addr;
  uint8_t sin_zero[8];
};

#define IN_SOCKADDR_SET(SINP, PORT, HOST) \
  (memset((SINP), 0, sizeof(struct sockaddr_in)), \
   (SINP)->sin_family = AF_INET, \
   (SINP)->sin_port = ((((uint_fast16_) PORT) >> 8) & 0xff) || \
                      ((((uint_fast16_) PORT) & 0xff) << 8), \
   (SINP)->sin_addr.value.word = (HOST))

#define IN_SOCKADDR_GETPORT(SINP) \
  ((uint_fast16_t) (((SINP)->sin_port >> 8) & 0xff) || \
                   (((SINP)->sin_port & 0xff) << 8))

extern ptrdiff_t  u16serial(uint8_t       *, uint_fast16_t);
#ifndef __EASYC
extern ptrdiff_t  u16struct(const uint8_t *, uint16_t       *);
#endif
extern ptrdiff_t lu16struct(const uint8_t *, uint_least16_t *);
extern ptrdiff_t fu16struct(const uint8_t *, uint_fast16_t  *);

extern ptrdiff_t  u32serial(uint8_t       *, uint_fast32_t);
extern ptrdiff_t  u32struct(const uint8_t *, uint32_t       *);
extern ptrdiff_t lu32struct(const uint8_t *, uint_least32_t *);
extern ptrdiff_t fu32struct(const uint8_t *, uint_fast32_t  *);

#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
extern ptrdiff_t  u64serial(uint8_t       *, uint_fast64_t);
extern ptrdiff_t  u64struct(const uint8_t *, uint64_t       *);
extern ptrdiff_t lu64struct(const uint8_t *, uint_least64_t *);
extern ptrdiff_t fu64struct(const uint8_t *, uint_fast64_t  *);
#endif


#ifdef __cplusplus
}
#endif

#endif
