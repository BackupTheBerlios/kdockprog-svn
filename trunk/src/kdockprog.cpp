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
#include <unistd.h>
#include "defines.h"
#include "kdockprog.h"
#include "kdockwidget.h"


/**
 * Ctor parses the options and sets its parameters according to them.
 * See parseOptions() for details.
 */
KDockProg::KDockProg( int argc, char * const *argv )
  : numPrograms(0), current(0)
{
  parseOptions( argc, argv );
}


/**
 * Dtor deletes all allocated program[] definitions.
 */
KDockProg::~KDockProg()
{
  for( int i = 0; i<numPrograms; i++ ) {
    delete program[i];
  }
}


/**
 * Return the program entry with the given number
 */
Program &KDockProg::operator[] ( int nr ) const
{
  if( nr >= 0 && nr<numPrograms )
    return *program[nr];
  throw 1;
}


/**
 * Parses the command line arguments.
 * The option -h prints out a usage information.
 * The option -i allocates a new QPixmap.
 * The option -e allocates a Program definition
 */
int KDockProg::parseOptions( int argc, char *const *argv )
{
  KDEBUG( ::fprintf( stderr, "KDockProg::parseOptions()\n" ););
  const QPixmap *icon = NULL;
  while( 1 ) {
    int c = getopt( argc, argv, "hi:e:" );
    if( -1 == c ) break;
    switch( c ) {
    case 'h':
      usage();
      exit(0);
      break;

    case 'i':
      icon = new QPixmap( optarg );
      if( icon->isNull() ) {
	::fprintf( stderr, "Cannot load icon \"%s\". Exiting.\n", optarg );
	exit(1);
      }
      break;

    case 'e':
      if( !icon ) {
	::fprintf( stderr, "You have to specify an icon with -i <icon>\n" );
	exit(1);
      }
      program[numPrograms++] = new Program( icon, optarg );
      break;
    }
  }

  return 0;
}


/**
 * Print out a usage information
 */
void KDockProg::usage( void )
{
  ::fprintf( stderr, "usage: kdockprog -i <icon> -e <command> [[-i <icon>] -e <command> [..]]\n\n" );
}


/**
 * Starts the program which is set in the current program entry.
 * Afterwards go to the next entry and switch the icon in the dockwidget.
 */
void KDockProg::startProgram( void )
{
  KDEBUG( ::fprintf( stderr, "KDockProg::startProgram()\n" ); );
  if( numPrograms > 0 ) {
    if( current >= 0 && current < numPrograms ) {
      const char *command = program[current]->getCommand();
      if( command ) {
	int ret = ::system( command );
	if( -1 == ret ) {
	  KERROR( "KDockProg::startProgram(): fork failed\n" );
	} else if( WIFEXITED( ret ) ) {
	  // Program exited normally
	  KDEBUG( ::fprintf( stderr, "KDockProg::startProgram(): "
			     "command exited normally\n" ); );
	  if( WEXITSTATUS( ret ) != 0 ) {
	     KWARN( ::fprintf( stderr, "KDockProg::startProgram(): "
			       "command returned %d\n",
			       WEXITSTATUS( ret ) ) );
	  }
	} else {
	  KWARN( ::fprintf( stderr, "KDockProg::startProgram(): "
			    "command terminated\n" ); );
	}
      }
      current++;
      if( current >= numPrograms ) current = 0;
      if( dock ) dock->setIcon( program[current]->getIcon() );
    }
  }
}

