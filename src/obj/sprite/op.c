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

#include <kernel.h>

#include <riscos/swi/OS.h>

#include "../riscos/sprite/op.h"
#include "../riscos/sprite/optypes.h"

_kernel_oserror *sprite_opswi(int sn, int op, const sprite_args *i,
                              sprite_args *o);

_kernel_oserror *sprite_op(int op, const sprite_args *i, sprite_args *o)
{
  return sprite_opswi(XOS_SpriteOp, op, i, o);
}

_kernel_oserror *sprite_opswi(int sno, int op, const sprite_args *i,
                              sprite_args *o)
{
  _kernel_swi_regs T;
  _kernel_oserror *err = 0;
  static _kernel_oserror invalid = { 255, "Invalid mode of operation" };

  T.r[0] = op;
  switch (op & ~0x300) {
  case sprite_Screen_Save:
    T.r[2] = (int) i->screenio.palette;
  case sprite_Screen_Load:
    T.r[1] = (int) i->screenio.pathname;
    if (op & 0x300) return &invalid;
    break;
  case sprite_Read_Area_Control_Block:
  case sprite_Initialise_Sprite_Area:
    T.r[1] = (int) i->area;
    break;
  case sprite_Load_Sprite_File:
  case sprite_Merge_Sprite_File:
  case sprite_Save_Sprite_File:
    T.r[2] = (int) i->areaio.pathname;
    T.r[1] = (int) i->areaio.area;
    break;
  case sprite_Return_Name:
    T.r[1] = (int) i->namereq.area;
    T.r[2] = (int) i->namereq.name;
    T.r[3] = i->namereq.len;
    T.r[4] = i->namereq.ord;
    break;
  case sprite_Get_Sprite_From_User_Coordinates:
    T.r[4] = i->get.rect->min.x;
    T.r[5] = i->get.rect->min.y;
    T.r[6] = i->get.rect->max.x;
    T.r[7] = i->get.rect->max.y;
  case sprite_Get_Sprite:
    if (op & 0x200) return &invalid;
    T.r[1] = (int) i->get.spec.byaddr.area;
    T.r[2] = (int) i->get.spec.byaddr.addr;
    T.r[3] = i->get.palette;
    break;
  case sprite_Create_Sprite:
    if (op & 0x200) return &invalid;
    T.r[1] = (int) i->dims.spec.byaddr.area;
    T.r[2] = (int) i->dims.spec.byaddr.addr;
    T.r[3] = i->dims.palette;
    T.r[4] = i->dims.width;
    T.r[5] = i->dims.height;
    T.r[6] = i->dims.mode;
    break;
  case sprite_Read_Sprite_Info:
  case sprite_Read_Save_Area_Size:
  case sprite_Delete_Sprite:
  case sprite_Select_Sprite:
  case sprite_Create_Mask:
  case sprite_Remove_Mask:
  case sprite_Flip_About_X_Axis:
  case sprite_Flip_About_Y_Axis:
  case sprite_Remove_Lefthand_Wastage:
    T.r[1] = (int) i->spec.byaddr.area;
    T.r[2] = (int) i->spec.byaddr.addr;
    break;
  case sprite_Copy_Sprite:
    if (op & 0x200) return &invalid;
  case sprite_Rename_Sprite:
    T.r[1] = (int) i->copy.spec.byaddr.area;
    T.r[2] = (int) i->copy.spec.byaddr.addr;
    T.r[3] = (int) i->copy.name;
    break;
  case sprite_Put_Sprite_Grey_Scaled:
  case sprite_Put_Sprite_Scaled:
    T.r[7] = (int) i->plot.pixtab;
  case sprite_Plot_Mask_Scaled:
    T.r[6] = (int) i->plot.scale;
  case sprite_Put_Sprite_At_User_Coordinates:
  case sprite_Plot_Mask_At_User_Coordinates:
    T.r[3] = i->plot.at->x;
    T.r[4] = i->plot.at->y;
  case sprite_Put_Sprite:
    T.r[5] = ((op & ~0x300) == sprite_Put_Sprite_Grey_Scaled) ?
      0 : i->plot.action;
  case sprite_Plot_Sprite_Mask:
    T.r[1] = (int) i->plot.spec.byaddr.area;
    T.r[2] = (int) i->plot.spec.byaddr.addr;
    break;
  case sprite_Insert_Or_Delete_Rows:
  case sprite_Insert_Or_Delete_Columns:
    T.r[4] = i->line.amount;
  case sprite_Insert_Row:
  case sprite_Delete_Row:
  case sprite_Insert_Column:
  case sprite_Delete_Column:
    T.r[1] = (int) i->line.spec.byaddr.area;
    T.r[2] = (int) i->line.spec.byaddr.addr;
    T.r[3] = i->line.number;
    break;
  case sprite_Append_Sprite:
    T.r[1] = (int) i->append.spec.byaddr.area;
    T.r[2] = (int) i->append.spec.byaddr.addr1;
    T.r[3] = (int) i->append.spec.byaddr.addr2;
    T.r[4] = i->append.vert;
    break;
  case sprite_Set_Pointer_Shape:
    T.r[1] = (int) i->pointer.spec.byaddr.area;
    T.r[2] = (int) i->pointer.spec.byaddr.addr;
    T.r[3] = i->pointer.bit.word;
    T.r[4] = i->pointer.at->x;
    T.r[5] = i->pointer.at->y;
    T.r[6] = (int) i->pointer.scale;
    T.r[7] = (int) i->pointer.pixtab;
    break;
  case sprite_Write_Pixel_Colour:
    T.r[6] = i->pixcol.tint;
  case sprite_Write_Pixel_Mask:
    T.r[5] = i->pixcol.col;
  case sprite_Read_Pixel_Colour:
  case sprite_Read_Pixel_Mask:
    T.r[1] = (int) i->pixcol.spec.byaddr.area;
    T.r[2] = (int) i->pixcol.spec.byaddr.addr;
    T.r[3] = i->pixcol.pix->x;
    T.r[4] = i->pixcol.pix->y;
    break;
  case sprite_Paint_Character_Scaled:
    T.r[0] = op & ~0x300;
    T.r[1] = i->charplot.c;
    T.r[3] = i->charplot.at->x;
    T.r[4] = i->charplot.at->y;
    T.r[6] = (int) i->charplot.scale;
    break;
  case sprite_Switch_Output_To_Sprite:
  case sprite_Switch_Output_To_Mask:
    T.r[1] = (int) i->redirect.spec.byaddr.area;
    T.r[2] = (int) i->redirect.spec.byaddr.addr;
    T.r[3] = (int) i->redirect.sa;
    break;
  case sprite_Create_Or_Remove_Palette:
    T.r[1] = (int) i->palette.spec.byaddr.area;
    T.r[2] = (int) i->palette.spec.byaddr.addr;
    T.r[3] = (int) i->palette.pal;
    break;
  case sprite_Plot_Mask_Transformed:
  case sprite_Plot_Sprite_Transformed:
    T.r[1] = (int) i->transform.spec.byaddr.area;
    T.r[2] = (int) i->transform.spec.byaddr.addr;
    T.r[3] = i->transform.bit.word;
    T.r[4] = (int) i->transform.from;
    T.r[5] = i->transform.action;
    T.r[6] = (int) i->transform.trans.dest;
    T.r[7] = (int) i->transform.pixtab;
    break;
  }

  err = _kernel_swi(sno, &T, &T);

  if (!err)
    switch (op & ~0x300) {
    case sprite_Read_Area_Control_Block:
      o->areadim.size = T.r[2];
      o->areadim.count = T.r[3];
      o->areadim.sprite1 = T.r[4];
      o->areadim.free1 = T.r[5];
      break;
    case sprite_Return_Name:
      o->size = T.r[3];
      break;
    case sprite_Get_Sprite_From_User_Coordinates:
    case sprite_Get_Sprite:
    case sprite_Select_Sprite:
      o->addr = (sprite_ptr) T.r[2];
      break;
    case sprite_Create_Or_Remove_Palette:
      o->palette.size = T.r[3];
      o->palette.pal = (void *) T.r[4];
      o->palette.mode = T.r[5];
      break;
    case sprite_Read_Sprite_Info:
      o->dims.mask = T.r[5];
      o->dims.width = T.r[3];
      o->dims.height = T.r[4];
      o->dims.mode = T.r[5];
      break;
    case sprite_Read_Pixel_Colour:
      o->pixcol.tint = T.r[6];
    case sprite_Read_Pixel_Mask:
      o->pixcol.col = T.r[5];
      break;
    case sprite_Switch_Output_To_Sprite:
    case sprite_Switch_Output_To_Mask:
      o->redirect.op = T.r[0];
      o->redirect.spec.byaddr.area = (sprite_area) T.r[1];
      o->redirect.spec.byaddr.addr = (sprite_ptr) T.r[2];
      o->redirect.sa = (void *) T.r[1];
      break;
    case sprite_Read_Save_Area_Size:
      o->size = T.r[3];
      break;
    }

  return err;
}

_kernel_oserror *sprite_restore(const sprite_redirectargs *b)
{
  _kernel_swi_regs T;

  T.r[0] = b->op;
  T.r[1] = (int) b->spec.byaddr.area;
  T.r[2] = (int) b->spec.byaddr.addr;
  T.r[3] = (int) b->sa;

  return _kernel_swi(XOS_SpriteOp, &T, &T);
}
