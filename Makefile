# Copyright by Benjamin Luxbacher

CXX = g++
CXXFLAGS = -c -Wall -std=c++11 -fpic
LIBINCLUDEFLAGS = -lcurl -ljsoncpp
LIBPATH = /usr/lib
INCPATH = /usr/include

EXCEPTIONOBJECTS = QRest/Exceptions/WebRequestException.o
QJOBEXECUTION = QRest/QJobExecution/QQueueResult.o QRest/QJobExecution/QExecution.o QRest/QJobExecution/QInfoQueue.o
QAVAILABLEBACKENDS = QRest/QAvailableBackends/QBackend.o
QWRAPPER = QRest/QWrapper/QWFactory.o QRest/QWrapper/QResponse/QResponse.o \
			QRest/QWrapper/QResponse/QResponseReal.o QRest/QWrapper/QResponse/QResponseRealDone.o \
			QRest/QWrapper/QResponse/QResponseRealUndone.o QRest/QWrapper/QResponse/QResponseSim.o \
			QRest/QWrapper/QResponse/QIP.o QRest/QWrapper/QResponse/QResult.o \
			QRest/QWrapper/QResponse/QParamsCustomize.o QRest/QWrapper/QResponse/QStatus.o \
			QRest/QWrapper/QResponse/QCalibration/QCalibration.o QRest/QWrapper/QResponse/QCalibration/QFridgeParameters.o \
			QRest/QWrapper/QResponse/QCalibration/QMultiQubitGates.o QRest/QWrapper/QResponse/QCalibration/QQubit.o \
			QRest/QWrapper/QResponse/QCalibration/QFridgeTemperature.o QRest/QWrapper/QResponse/QCalibration/QGateError.o \
			QRest/QWrapper/QResponse/QCalibration/QQubitContent.o \
			QRest/QWrapper/QResponse/QCode/QCode.o QRest/QWrapper/QResponse/QCode/QJsonQASM.o \
			QRest/QWrapper/QResponse/QCode/QPlayground.o QRest/QWrapper/QResponse/QCode/QGate.o \
			QRest/QWrapper/QResponse/QCode/QTopology.o QRest/QWrapper/QResponse/QCode/QMeasureCreg.o \
			QRest/QWrapper/QResponse/QCode/QReg.o QRest/QWrapper/QResponse/QData/QData.o \
			QRest/QWrapper/QResponse/QData/QAdditionalData.o QRest/QWrapper/QResponse/QData/QDataP.o
QRESTOBJECTS = $(EXCEPTIONOBJECTS) $(QJOBEXECUTION) $(QAVAILABLEBACKENDS) $(QWRAPPER) QRest/RestConnection.o

QMAPPEROBJECTS = QMapper/mGate.o QMapper/mArchitecture.o QMapper/mCircuit.o

OBJECTS = $(QRESTOBJECTS) $(QMAPPEROBJECTS)



all: libqiskit.so

libqiskit.so: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBINCLUDEFLAGS) -shared -o libqiskit.so

$(QRESTOBJECTS):
	cd QRest && $(MAKE)

$(QMAPPEROBJECTS):
	cd QMapper && $(MAKE)

install:
	install ./libqiskit.so $(LIBPATH)

	mkdir $(INCPATH)/libqiskit
	(find . -iname '*.h' -print | tar --create --files-from -) | (cd $(INCPATH)/libqiskit && tar xvfp -)
	cp ./libqiskit.h $(INCPATH)/libqiskit
	find $(INCPATH)/libqiskit -iname "*.h" -exec sudo chmod -R u=rw,g=r,o=r {} \;

uninstall:
	rm -f $(LIBPATH)/libqiskit.so

	rm -rf $(INCPATH)/libqiskit

clean:
	rm -f *.o
	cd QRest && $(MAKE) clean
	cd QMapper && $(MAKE) clean

clear: clean
	rm -f libqiskit.so