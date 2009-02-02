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

#ifndef _KDOCKPROG_H_
#define _KDOCKPROG_H_

#include <qobject.h>
#include <qpixmap.h>

#include "program.h"

class KDockWidget;

/**
 * Main class.
 * Manages the program entries and the dock widget
 */
class KDockProg: public QObject
{
  Q_OBJECT
public:
  KDockProg( int, char * const* );
  ~KDockProg();
  int getNumPrograms( void ) const { return numPrograms; }
  Program &operator[] ( int ) const;
  void usage( void );
  void setDockWidget( KDockWidget &d ) { dock = &d; }

public slots:
  void startProgram();

private:
  enum { MAX_PROGS = 100 }; 
  int parseOptions( int, char * const* );
  Program *program[ MAX_PROGS ];
  int numPrograms;
  int current;
  KDockWidget *dock;
};

#endif // _KDOCKPROG_H_
