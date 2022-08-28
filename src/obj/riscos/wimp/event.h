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

#ifndef Yacitros_wimp_event
#define Yacitros_wimp_event

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define wimp_Null_Reason_Code         UINT32_C(0)
#define wimp_Redraw_Window_Request    UINT32_C(1)
#define wimp_Open_Window_Request      UINT32_C(2)
#define wimp_Close_Window_Request     UINT32_C(3)
#define wimp_Pointer_Leaving_Window   UINT32_C(4)
#define wimp_Pointer_Entering_Window  UINT32_C(5)
#define wimp_Mouse_Click              UINT32_C(6)
#define wimp_User_Drag_Box            UINT32_C(7)
#define wimp_Key_Pressed              UINT32_C(8)
#define wimp_Menu_Selection           UINT32_C(9)
#define wimp_Scroll_Request           UINT32_C(10)
#define wimp_Lose_Caret               UINT32_C(11)
#define wimp_Gain_Caret               UINT32_C(12)
#define wimp_User_Message             UINT32_C(17)
#define wimp_User_Message_Recorded    UINT32_C(18)
#define wimp_User_Message_Acknowledge UINT32_C(19)

#ifdef __cplusplus
}
#endif

#endif
