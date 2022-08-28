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

#include "../riscos/vdu/var.h"
#include "../riscos/vdu/modevars.h"

#include "../yacitros/desktop/mode.h"

#include "throw.h"

int mode_getgeom(mode_geom *p)
{
  THROW(vdu_readmodevariable(NULL, -1, vdu_ScrRCol,
                             (vdu_varval *) &p->text.area.max.x));
  THROW(vdu_readmodevariable(NULL, -1, vdu_ScrBRow,
                             (vdu_varval *) &p->text.area.max.y));
  p->text.area.min.x = p->text.area.min.y = 0;
  p->text.area.max.x++;
  p->text.area.max.y++;

  THROW(vdu_readmodevariable(NULL, -1, vdu_XWindLimit,
                             (vdu_varval *) &p->graphics.area.max.x));
  THROW(vdu_readmodevariable(NULL, -1, vdu_YWindLimit,
                             (vdu_varval *) &p->graphics.area.max.y));
  p->graphics.area.min.x = p->graphics.area.min.y = 0;
  p->graphics.area.max.x++;
  p->graphics.area.max.y++;

  THROW(vdu_readmodevariable(NULL, -1, vdu_XEigFactor,
                             (vdu_varval *) &p->graphics.scale.xmul));
  THROW(vdu_readmodevariable(NULL, -1, vdu_YEigFactor,
                             (vdu_varval *) &p->graphics.scale.ymul));
  p->graphics.scale.xdiv = p->graphics.scale.ydiv = 1;
  p->graphics.scale.xmul = 1<<p->graphics.scale.xmul;
  p->graphics.scale.ymul = 1<<p->graphics.scale.ymul;

  return 0;
}
