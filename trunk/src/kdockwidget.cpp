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
#include <string.h>

// Qt includes
#include <qwidget.h>
#include <qpixmap.h>
#include <qstring.h>
#include <qtimer.h>

// KDE includes
#include <ksystemtray.h>
#include <kpopupmenu.h>

// Application includes
#include "defines.h"
#include "kdockwidget.h"

const QString KDockWidget::title( "KDockProg" );

/**
 * Ctor of the system tray docking icon
 *
 * Loads the icons, initializes the popup menu.
 */
KDockWidget::KDockWidget( QWidget *parent )
  : KSystemTray( parent ), icon(NULL) //, numIcons(0), current(0)
{
  KDEBUG( ::fprintf( stderr, "KDockWidget::KDockWidget()\n" ) );
  if( contextMenu() ) {
    contextMenu()->changeTitle( contextMenu()->idAt(0), NULL, title );
  }
  show();
}


/**
 * Dtor frees the reserved resources
 */
KDockWidget::~KDockWidget()
{
  KDEBUG( ::fprintf( stderr, "KDockWidget::~KDockWidget()\n" ) );
}


/**
 * Updates the icon according to found and animation state.
 */
void KDockWidget::updateIcon( void )
{
  KDEBUG( ::fprintf( stderr, "KDockWidget::updateIcon()\n" ) );
  if( NULL != icon ) {
    setPixmap( *icon );
    if( contextMenu() ) {
      contextMenu()->changeTitle( contextMenu()->idAt(0), *icon, title );
    }
  }
}


/**
 * Sets the icon of the dock widget to the given one
 */
void KDockWidget::setIcon( const QPixmap *pixmap )
{
  KDEBUG( ::fprintf( stderr, "KDockWidget::setIcon()\n" ) );
  icon = pixmap;
  updateIcon();
}


/**
 * React to a mouse press event:
 * A left click starts the program of the current state.
 * A right click opens the context menu.
 */
void KDockWidget::mousePressEvent( QMouseEvent *event )
{
  if( !event ) return;
  switch( event->button() ) {
  case Qt::LeftButton:
    emit iconPressed();
    break;
  case Qt::RightButton:
    KSystemTray::mousePressEvent( event );
    break;
  }
}
