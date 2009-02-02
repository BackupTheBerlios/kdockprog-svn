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

#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <stdlib.h>

#include <qpixmap.h>

/**
 * Stores the data for a program entry.
 * That is an icon, the command and the number of the icon in the 
 * dockwidget.
 */
class Program
{
public:
  Program( const QPixmap *, const char * );
  ~Program();
  const QPixmap *getIcon() const { return icon; }
  const char *getCommand() const { return command; }

private:
  const QPixmap *icon;     ///< Stored icon
  char          *command;  ///< Command to execute
};

#endif // _PROGRAM_H_
