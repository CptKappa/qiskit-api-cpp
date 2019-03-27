# Copyright by Benjamin Luxbacher

CXX = g++
CXXFLAGS = -c -Wall -std=c++11 -fpic

EXCEPTIONOBJECTS = WebRequestException.o

all: $(EXCEPTIONOBJECTS)

WebRequestException.o: WebRequestException.cpp WebRequestException.h
	$(CXX) WebRequestException.cpp -o WebRequestException.o $(CXXFLAGS)

clean:
	rm -f *.o