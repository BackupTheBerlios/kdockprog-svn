/*
    This file is part of KDockProg.
    Copyright (C) 2005-2009 Tobias Elbrandt

    KDockProg is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    KDockProg is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with KDockProg.  If not, see <http://www.gnu.org/licenses/>.

    KDockProg was written by Tobias Elbrandt and put under GPL in 2009.
*/

#include <string.h>

#include "defines.h"
#include "program.h"

/**
 * Ctor sets the icon and copies the command string
 */
Program::Program( const QPixmap *icon0, const char *command0 ): icon(icon0)
{
  if( command0 ) {
    command = ::strdup(command0);
  } else {
    command = NULL;
  }
}

Program::~Program()
{
  if( command ) {
    ::free( command );
  }
}
