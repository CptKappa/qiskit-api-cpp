# Copyright by Benjamin Luxbacher

CXX = g++
CXXFLAGS = -c -Wall -std=c++11 -fpic

QWRAPPER = QWFactory.o QResponse/QResponse.o \
			QResponse/QResponseReal.o QResponse/QResponseRealDone.o \
			QResponse/QResponseRealUndone.o QResponse/QResponseSim.o \
			QResponse/QIP.o QResponse/QResult.o \
			QResponse/QParamsCustomize.o QResponse/QStatus.o \
			QResponse/QCalibration/QCalibration.o QResponse/QCalibration/QFridgeParameters.o \
			QResponse/QCalibration/QMultiQubitGates.o QResponse/QCalibration/QQubit.o \
			QResponse/QCalibration/QFridgeTemperature.o QResponse/QCalibration/QGateError.o \
			QResponse/QCalibration/QQubitContent.o \
			QResponse/QCode/QCode.o QResponse/QCode/QJsonQASM.o \
			QResponse/QCode/QPlayground.o QResponse/QCode/QGate.o \
			QResponse/QCode/QTopology.o QResponse/QCode/QMeasureCreg.o \
			QResponse/QCode/QReg.o QResponse/QData/QData.o \
			QResponse/QData/QAdditionalData.o QResponse/QData/QDataP.o

all: $(QWRAPPER)

QWFactory.o: QWFactory.cpp QWFactory.h \
						QResponse/QResponse.o \
						QResponse/QResponseRealDone.o \
						QResponse/QResponseRealUndone.o \
						QResponse/QResponseSim.o
	$(CXX) QWFactory.cpp -o QWFactory.o $(CXXFLAGS)

QResponse/QResponse.o: QResponse/QResponse.cpp QResponse/QResponse.h \
								QResponse/QResult.o \
								QResponse/QStatus.o \
								QResponse/QIP.o \
								QResponse/QCalibration/QCalibration.o \
								QResponse/QParamsCustomize.o \
								QResponse/QCode/QCode.o
	$(CXX) QResponse/QResponse.cpp -o QResponse/QResponse.o $(CXXFLAGS)

QResponse/QResponseReal.o: QResponse/QResponseReal.cpp QResponse/QResponseReal.h \
									QResponse/QResponse.o
	$(CXX) QResponse/QResponseReal.cpp -o QResponse/QResponseReal.o $(CXXFLAGS)

QResponse/QResponseRealDone.o: QResponse/QResponseRealDone.cpp QResponse/QResponseRealDone.h \
										QResponse/QResponseReal.o
	$(CXX) QResponse/QResponseRealDone.cpp -o QResponse/QResponseRealDone.o $(CXXFLAGS)

QResponse/QResponseRealUndone.o: QResponse/QResponseRealUndone.cpp QResponse/QResponseRealUndone.h \
											QResponse/QResponseReal.o
	$(CXX) QResponse/QResponseRealUndone.cpp -o QResponse/QResponseRealUndone.o $(CXXFLAGS)

QResponse/QResponseSim.o: QResponse/QResponseSim.cpp QResponse/QResponseSim.h \
									QResponse/QResponse.o \
									QResponse/QCode/QCode.o
	$(CXX) QResponse/QResponseSim.cpp -o QResponse/QResponseSim.o $(CXXFLAGS)

QResponse/QIP.o: QResponse/QIP.cpp QResponse/QIP.h
	$(CXX) QResponse/QIP.cpp -o QResponse/QIP.o $(CXXFLAGS)

QResponse/QResult.o: QResponse/QResult.cpp QResponse/QResult.h \
								QResponse/QData/QData.o
	$(CXX) QResponse/QResult.cpp -o QResponse/QResult.o $(CXXFLAGS)

QResponse/QParamsCustomize.o: QResponse/QParamsCustomize.cpp QResponse/QParamsCustomize.h
	$(CXX) QResponse/QParamsCustomize.cpp -o QResponse/QParamsCustomize.o $(CXXFLAGS)

QResponse/QStatus.o: QResponse/QStatus.cpp QResponse/QStatus.h
	$(CXX) QResponse/QStatus.cpp -o QResponse/QStatus.o $(CXXFLAGS)


QResponse/QCalibration/QCalibration.o: QResponse/QCalibration/QCalibration.cpp QResponse/QCalibration/QCalibration.h \
												QResponse/QCalibration/QFridgeParameters.o \
												QResponse/QCalibration/QQubit.o \
												QResponse/QCalibration/QMultiQubitGates.o
	$(CXX) QResponse/QCalibration/QCalibration.cpp -o QResponse/QCalibration/QCalibration.o $(CXXFLAGS)

QResponse/QCalibration/QFridgeParameters.o: QResponse/QCalibration/QFridgeParameters.cpp QResponse/QCalibration/QFridgeParameters.h \
														QResponse/QCalibration/QFridgeTemperature.o
	$(CXX) QResponse/QCalibration/QFridgeParameters.cpp -o QResponse/QCalibration/QFridgeParameters.o $(CXXFLAGS)

QResponse/QCalibration/QMultiQubitGates.o: QResponse/QCalibration/QMultiQubitGates.cpp QResponse/QCalibration/QMultiQubitGates.h \
													QResponse/QCalibration/QGateError.o
	$(CXX) QResponse/QCalibration/QMultiQubitGates.cpp -o QResponse/QCalibration/QMultiQubitGates.o $(CXXFLAGS)

QResponse/QCalibration/QQubit.o: QResponse/QCalibration/QQubit.cpp QResponse/QCalibration/QQubit.h \
											QResponse/QCalibration/QQubitContent.o
	$(CXX) QResponse/QCalibration/QQubit.cpp -o QResponse/QCalibration/QQubit.o $(CXXFLAGS)

QResponse/QCalibration/QFridgeTemperature.o: QResponse/QCalibration/QFridgeTemperature.cpp QResponse/QCalibration/QFridgeTemperature.h
	$(CXX) QResponse/QCalibration/QFridgeTemperature.cpp -o QResponse/QCalibration/QFridgeTemperature.o $(CXXFLAGS)

QResponse/QCalibration/QGateError.o: QResponse/QCalibration/QGateError.cpp QResponse/QCalibration/QGateError.h
	$(CXX) QResponse/QCalibration/QGateError.cpp -o QResponse/QCalibration/QGateError.o $(CXXFLAGS)

QResponse/QCalibration/QQubitContent.o: QResponse/QCalibration/QQubitContent.cpp QResponse/QCalibration/QQubitContent.h
	$(CXX) QResponse/QCalibration/QQubitContent.cpp -o QResponse/QCalibration/QQubitContent.o $(CXXFLAGS)


QResponse/QCode/QCode.o: QResponse/QCode/QCode.cpp QResponse/QCode/QCode.h \
									QResponse/QCode/QJsonQASM.o
	$(CXX) QResponse/QCode/QCode.cpp -o QResponse/QCode/QCode.o $(CXXFLAGS)

QResponse/QCode/QJsonQASM.o: QResponse/QCode/QJsonQASM.cpp QResponse/QCode/QJsonQASM.h \
										QResponse/QCode/QTopology.o \
										QResponse/QCode/QPlayground.o
	$(CXX) QResponse/QCode/QJsonQASM.cpp -o QResponse/QCode/QJsonQASM.o $(CXXFLAGS)

QResponse/QCode/QPlayground.o: QResponse/QCode/QPlayground.cpp QResponse/QCode/QPlayground.h \
						QResponse/QCode/QGate.o
	$(CXX) QResponse/QCode/QPlayground.cpp -o QResponse/QCode/QPlayground.o $(CXXFLAGS)

QResponse/QCode/QGate.o: QResponse/QCode/QGate.cpp QResponse/QCode/QGate.h \
									QResponse/QCode/QMeasureCreg.o
	$(CXX) QResponse/QCode/QGate.cpp -o QResponse/QCode/QGate.o $(CXXFLAGS)

QResponse/QCode/QTopology.o: QResponse/QCode/QTopology.cpp QResponse/QCode/QTopology.h \
										QResponse/QCode/QReg.o
	$(CXX) QResponse/QCode/QTopology.cpp -o QResponse/QCode/QTopology.o $(CXXFLAGS)

QResponse/QCode/QMeasureCreg.o: QResponse/QCode/QMeasureCreg.cpp QResponse/QCode/QMeasureCreg.h
	$(CXX) QResponse/QCode/QMeasureCreg.cpp -o QResponse/QCode/QMeasureCreg.o $(CXXFLAGS)

QResponse/QCode/QReg.o: QResponse/QCode/QReg.cpp QResponse/QCode/QReg.h
	$(CXX) QResponse/QCode/QReg.cpp -o QResponse/QCode/QReg.o $(CXXFLAGS)


QResponse/QData/QData.o: QResponse/QData/QData.cpp QResponse/QData/QData.h \
									QResponse/QData/QAdditionalData.o \
									QResponse/QData/QDataP.o
	$(CXX) QResponse/QData/QData.cpp -o QResponse/QData/QData.o $(CXXFLAGS)

QResponse/QData/QAdditionalData.o: QResponse/QData/QAdditionalData.cpp QResponse/QData/QAdditionalData.h
	$(CXX) QResponse/QData/QAdditionalData.cpp -o QResponse/QData/QAdditionalData.o $(CXXFLAGS)

QResponse/QData/QDataP.o: QResponse/QData/QDataP.cpp QResponse/QData/QDataP.h
	$(CXX) QResponse/QData/QDataP.cpp -o QResponse/QData/QDataP.o $(CXXFLAGS)

clean:
	rm -f *.o
	rm -f QResponse/*.o
	rm -f QResponse/QCalibration/*.o
	rm -f QResponse/QCode/*.o
	rm -f QResponse/QData/*.o