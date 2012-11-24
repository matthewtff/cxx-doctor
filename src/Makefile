#CC=g++
CC=clang++
WARNINGS=-Wall -Wextra -Wold-style-cast -Woverloaded-virtual
#CFLAGS=-c -std=c++0x -stdlib=libc++ -g -ggdb -D_DEBUG
CFLAGS=-c -std=c++0x -O2 -stdlib=libc++ -g
INC=-I../external/inc
KOOHARLIB=koohar
OODBLIB=oodb
PTHREADLIB=pthread
OPENSSLLIB=ssl
BOOSTLIB=boost_system
LIBDIR=../external/lib
LIB=-L$(LIBDIR) -l$(KOOHARLIB) -l$(OODBLIB) -l$(PTHREADLIB) -l$(OPENSSLLIB) -l$(BOOSTLIB)

SOURCES=doctor.cc register.cc medic.cc patient.cc servey.cc device.cc\
visit.cc inmate.cc insurance.cc machine.cc md5.cc crypting.cc disease.cc\
settings.cc
OBJECTS=$(SOURCES:.cc=.o)

all: doctor

doctor: $(OBJECTS)
#	$(CC) -g -ggdb -stdlib=libc++ $(WARNINGS) *.o -o doctor $(LIB)
	$(CC) -g -O2 -stdlib=libc++ $(WARNINGS) *.o -o doctor $(LIB)

.cc.o:
	$(CC) $(WARNINGS) $(CFLAGS) $(INC) $< -o $@

rebuild: clean all

relink:
	$(CC) -g -ggdb -stdlib=libc++ $(WARNINGS) *.o -o doctor $(LIB)


clean:
	rm *.o doctor
