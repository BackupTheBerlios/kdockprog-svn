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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include <qpixmap.h>
#include <kapp.h>

#include "defines.h"
#include "kdockwidget.h"
#include "kdockprog.h"

/**
 * Main program
 */
int main( int argc, char *argv[] )
{
  KApplication app( argc, argv, "kdockprog" );
  KDockProg &prog = *new KDockProg( argc, argv );
  if( 0 == prog.getNumPrograms() ) {
    ::fprintf( stderr, "You have to specify at least one -i -e pair.\n" );
    prog.usage();
    exit(1);
  }

  KDockWidget dock(NULL);
  prog.setDockWidget( dock );
  dock.connect( &dock, SIGNAL(quitSelected()), &app, SLOT(quit()));
  dock.setIcon( prog[0].getIcon() );
  dock.connect( &dock, SIGNAL(iconPressed()), &prog, SLOT(startProgram()) );

  return app.exec();
}
