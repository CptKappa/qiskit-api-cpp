# Copyright by Benjamin Luxbacher

CXX = g++
CXXFLAGS = -c -Wall -std=c++11 -fpic

EXCEPTIONOBJECTS = Exceptions/WebRequestException.o
QJOBEXECUTION = QJobExecution/QQueueResult.o QJobExecution/QExecution.o QJobExecution/QInfoQueue.o
QAVAILABLEBACKENDS = QAvailableBackends/QBackend.o
QWRAPPER = QWrapper/QWFactory.o QWrapper/QResponse/QResponse.o \
			QWrapper/QResponse/QResponseReal.o QWrapper/QResponse/QResponseRealDone.o \
			QWrapper/QResponse/QResponseRealUndone.o QWrapper/QResponse/QResponseSim.o \
			QWrapper/QResponse/QIP.o QWrapper/QResponse/QResult.o \
			QWrapper/QResponse/QParamsCustomize.o QWrapper/QResponse/QStatus.o \
			QWrapper/QResponse/QCalibration/QCalibration.o QWrapper/QResponse/QCalibration/QFridgeParameters.o \
			QWrapper/QResponse/QCalibration/QMultiQubitGates.o QWrapper/QResponse/QCalibration/QQubit.o \
			QWrapper/QResponse/QCalibration/QFridgeTemperature.o QWrapper/QResponse/QCalibration/QGateError.o \
			QWrapper/QResponse/QCalibration/QQubitContent.o \
			QWrapper/QResponse/QCode/QCode.o QWrapper/QResponse/QCode/QJsonQASM.o \
			QWrapper/QResponse/QCode/QPlayground.o QWrapper/QResponse/QCode/QGate.o \
			QWrapper/QResponse/QCode/QTopology.o QWrapper/QResponse/QCode/QMeasureCreg.o \
			QWrapper/QResponse/QCode/QReg.o QWrapper/QResponse/QData/QData.o \
			QWrapper/QResponse/QData/QAdditionalData.o QWrapper/QResponse/QData/QDataP.o
OBJECTS = $(EXCEPTIONOBJECTS) $(QJOBEXECUTION) $(QAVAILABLEBACKENDS) $(QWRAPPER) RestConnection.o



all: $(OBJECTS)


RestConnection.o: RestConnection.cpp RestConnection.h
	$(CXX) RestConnection.cpp -o RestConnection.o $(CXXFLAGS)
	
$(QAVAILABLEBACKENDS):
	cd QAvailableBackends && $(MAKE)

$(EXCEPTIONOBJECTS):
	cd Exceptions && $(MAKE)

$(QJOBEXECUTION):
	cd QJobExecution && $(MAKE)

$(QWRAPPER):
	cd QWrapper && $(MAKE)

clean:
	rm -f *.o

	cd Exceptions && $(MAKE) clean
	cd QJobExecution && $(MAKE) clean
	cd QAvailableBackends && $(MAKE) clean
	cd QWrapper && $(MAKE) clean