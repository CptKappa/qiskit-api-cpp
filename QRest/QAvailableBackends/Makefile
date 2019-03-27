# Copyright by Benjamin Luxbacher

CXX = g++
CXXFLAGS = -c -Wall -std=c++11 -fpic

QAVAILABLEBACKENDS = QBackend.o

all: $(QAVAILABLEBACKENDS)

QBackend.o: QBackend.cpp QBackend.h
	$(CXX) QBackend.cpp -o QBackend.o $(CXXFLAGS)

clean:
	rm -f *.o