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

#ifndef Yacitros_sprite_optypes
#define Yacitros_sprite_optypes

#ifdef __cplusplus
extern "C" {
#endif


#define sprite_Screen_Save                      0x02
#define sprite_Screen_Load                      0x03
#define sprite_Read_Area_Control_Block          0x08
#define sprite_Initialise_Sprite_Area           0x09
#define sprite_Load_Sprite_File                 0x0a
#define sprite_Merge_Sprite_File                0x0b
#define sprite_Save_Sprite_File                 0x0c
#define sprite_Return_Name                      0x0d
#define sprite_Get_Sprite                       0x0e
#define sprite_Create_Sprite                    0x0f
#define sprite_Get_Sprite_From_User_Coordinates 0x10
#define sprite_Select_Sprite                    0x18
#define sprite_Delete_Sprite                    0x19
#define sprite_Rename_Sprite                    0x1a
#define sprite_Copy_Sprite                      0x1b
#define sprite_Put_Sprite                       0x1c
#define sprite_Create_Mask                      0x1d
#define sprite_Remove_Mask                      0x1e
#define sprite_Insert_Row                       0x1f
#define sprite_Delete_Row                       0x20
#define sprite_Flip_About_X_Axis                0x21
#define sprite_Put_Sprite_At_User_Coordinates   0x22
#define sprite_Append_Sprite                    0x23
#define sprite_Set_Pointer_Shape                0x24
#define sprite_Create_Or_Remove_Palette         0x25
#define sprite_Read_Sprite_Info                 0x28
#define sprite_Read_Pixel_Colour                0x29
#define sprite_Write_Pixel_Colour               0x2a
#define sprite_Read_Pixel_Mask                  0x2b
#define sprite_Write_Pixel_Mask                 0x2c
#define sprite_Insert_Column                    0x2d
#define sprite_Delete_Column                    0x2e
#define sprite_Flip_About_Y_Axis                0x2f
#define sprite_Plot_Sprite_Mask                 0x30
#define sprite_Plot_Mask_At_User_Coordinates    0x31
#define sprite_Plot_Mask_Scaled                 0x32
#define sprite_Paint_Character_Scaled           0x33
#define sprite_Put_Sprite_Scaled                0x34
#define sprite_Put_Sprite_Grey_Scaled           0x35
#define sprite_Remove_Lefthand_Wastage          0x36
#define sprite_Plot_Mask_Transformed            0x37
#define sprite_Plot_Sprite_Transformed          0x38
#define sprite_Insert_Or_Delete_Rows            0x39
#define sprite_Insert_Or_Delete_Columns         0x3a
#define sprite_Switch_Output_To_Sprite          0x3c
#define sprite_Switch_Output_To_Mask            0x3d
#define sprite_Read_Save_Area_Size              0x3e

#ifdef __cplusplus
}
#endif

#endif
