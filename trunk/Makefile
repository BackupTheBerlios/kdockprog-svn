# Check the machine we are compiling on and set libpath accordingly
MACHINE=$(shell uname -m)
ifeq "$(MACHINE)" "x86_64"
	LIBPATH=lib64
else
	LIBPATH=lib
endif

PROG=kdockprog
QTDIR=/usr/lib/qt3
QTINCDIR=$(QTDIR)/include
QTLIBDIR=$(QTDIR)/$(LIBPATH)
KDEDIR=/opt/kde3
KDEINCDIR=$(KDEDIR)/include
KDELIBDIR=$(KDEDIR)/$(LIBPATH)
INCDIRS=-Iinclude -I$(QTINCDIR) -I$(KDEINCDIR)
LIBDIRS=-L$(QTLIBDIR) -L$(KDELIBDIR)
LIBS=-lkdeui -lqt-mt

OPTFLAGS=-g2 -O0
CFLAGS=$(INCDIRS) $(OPTFLAGS)
LDFLAGS=$(LIBDIRS) $(LIBS)

INCLUDES=$(wildcard include/*.h)
MOCSRC=$(patsubst include/%.h,src/moc_%.cpp,$(INCLUDES))
SRC=$(wildcard src/*.cpp) $(MOCSRC)
OBJ=$(patsubst src/%.cpp,obj/%.o,$(SRC))
#MOC_OBJ=moc_kdockwidget.o moc_kdockprog.o program.o

final:  OPTFLAGS = -g0 -O3 -DNDEBUG
final:  all
	strip $(PROG)

debug:	OPTFLAGS = -g2 -O0
debug:	all

all:	$(PROG)

$(PROG):	$(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

obj/%.o:	src/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $^

src/moc_%.cpp:	include/%.h
	moc $< -o $@


fresh:	clean all

clean:
	-rm -f obj/*.o src/*~ include/*~ src/moc_*.cpp kdockprog

# dependencies
main.o:		main.cpp defines.h kdockwidget.h kdockprog.h
kdockwidget.o:	kdockwidget.cpp defines.h kdockwidget.h
kdockprog.o:	kdockprog.cpp defines.h kdockprog.h program.h
program.o:	program.cpp defines.h

