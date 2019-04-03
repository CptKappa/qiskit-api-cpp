# Copyright by Benjamin Luxbacher

CXX = g++
CXXFLAGS = -c -Wall -std=c++11 -fpic

QMAPPEROBJECTS = mGate.o mArchitecture.o mCircuit.o
LIBPATH = /usr/lib

all: $(QMAPPEROBJECTS)


mGate.o: mGate.cpp mGate.h
	$(CXX) mGate.cpp -o mGate.o $(CXXFLAGS)

mArchitecture.o: mArchitecture.cpp mArchitecture.h
	$(CXX) mArchitecture.cpp -o mArchitecture.o $(CXXFLAGS)
	
mCircuit.o: mCircuit.cpp mCircuit.h \
			mGate.h mArchitecture.h
	$(CXX) mCircuit.cpp -o mCircuit.o $(CXXFLAGS)

clean:
	rm -f *.o

install:
	install ./libQmapper.so $(LIBPATH)

uninstall:
	rm -f $(LIBPATH)/libQmapper.so

test: all
	$(CXX) mGate.o mArchitecture.o mCircuit.o -shared -o libQmapper.so