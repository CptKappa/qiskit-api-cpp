#ifndef QCALIBRATION_CPP_INCLUDED
#define QCALIBRATION_CPP_INCLUDED

#include "QCalibration.h"

namespace QRest
{
	namespace QWrapper
	{
		QCalibration::QCalibration()
		{

		}

		QCalibration::QCalibration(std::string lastUpdateDate, QFridgeParameters fridgeParameters, std::list<QQubit> qubits, std::list<QMultiQubitGates> multiQubitGates, std::string version)
		{
			this->lastUpdateDate = lastUpdateDate;
			this->fridgeParameters = fridgeParameters;
			this->qubits = qubits;
			this->multiQubitGates = multiQubitGates;
			this->version = version;
		}
	}
}

#endif