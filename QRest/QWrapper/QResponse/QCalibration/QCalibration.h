#ifndef QCALIBRATION_H_INCLUDED__
#define QCALIBRATION_H_INCLUDED__
#include <string>
#include <list>
#include "QFridgeParameters.h"
#include "QQubit.h"
#include "QMultiQubitGates.h"

namespace QRest
{
	namespace QWrapper
	{
		class QCalibration
		{
			public:
				QCalibration();
				QCalibration(std::string, QFridgeParameters, std::list<QQubit>, std::list<QMultiQubitGates>, std::string);
				
				std::string lastUpdateDate;
				QFridgeParameters fridgeParameters;
				std::list<QQubit> qubits;
				std::list<QMultiQubitGates> multiQubitGates;
				std::string version;
		};
	}
}

#endif