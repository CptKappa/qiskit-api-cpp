# Copyright by Benjamin Luxbacher

CXX = g++
CXXFLAGS = -c -Wall -std=c++11 -fpic

QJOBEXECUTION = QQueueResult.o QExecution.o QInfoQueue.o

all: $(QJOBEXECUTION)

QQueueResult.o: QQueueResult.cpp QQueueResult.h
	$(CXX) QQueueResult.cpp -o QQueueResult.o $(CXXFLAGS)

QExecution.o: QExecution.cpp QExecution.h
	$(CXX) QExecution.cpp -o QExecution.o $(CXXFLAGS)

QInfoQueue.o: QInfoQueue.cpp QInfoQueue.h
	$(CXX) QInfoQueue.cpp -o QInfoQueue.o $(CXXFLAGS)

clean:
	rm -f *.o