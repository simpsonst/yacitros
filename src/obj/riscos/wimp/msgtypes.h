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

#ifndef Yacitros_wimp_msgtypes
#define Yacitros_wimp_msgtypes

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define wimp_Message_Quit                       UINT32_C(0x00000)
#define wimp_Message_DataSave                   UINT32_C(0x00001)
#define wimp_Message_DataSaveAck                UINT32_C(0x00002)
#define wimp_Message_DataLoad                   UINT32_C(0x00003)
#define wimp_Message_DataLoadAck                UINT32_C(0x00004)
#define wimp_Message_DataOpen                   UINT32_C(0x00005)
#define wimp_Message_RAMFetch                   UINT32_C(0x00006)
#define wimp_Message_RAMTransmit                UINT32_C(0x00007)
#define wimp_Message_PreQuit                    UINT32_C(0x00008)
#define wimp_Message_PaletteChange              UINT32_C(0x00009)
#define wimp_Message_SaveDesktop                UINT32_C(0x0000a)

#define wimp_Message_FilerOpenDir               UINT32_C(0x00400)
#define wimp_Message_FilerCloseDir              UINT32_C(0x00401)

#define wimp_Message_HelpRequest                UINT32_C(0x00502)
#define wimp_Message_HelpReply                  UINT32_C(0x00503)

#define wimp_Message_Notify                     UINT32_C(0x40040)

#define wimp_Message_MenuWarning                UINT32_C(0x400c0)
#define wimp_Message_MenusDeleted               UINT32_C(0x400c9)

#define wimp_Message_ModeChange                 UINT32_C(0x400c1)

#define wimp_Message_TaskInitialise             UINT32_C(0x400c2)
#define wimp_Message_TaskCloseDown              UINT32_C(0x400c3)
#define wimp_Message_TaskNameRq                 UINT32_C(0x400c6)
#define wimp_Message_TaskNameIs                 UINT32_C(0x400c7)

#define wimp_Message_SlotSize                   UINT32_C(0x400c4)
#define wimp_Message_SetSlot                    UINT32_C(0x400c5)

#ifdef __cplusplus
}
#endif

#endif
