#ifndef QFRIDGEPARAMETERS_H_INCLUDED__
#define QFRIDGEPARAMETERS_H_INCLUDED__
#include <string>
#include "QFridgeTemperature.h"

namespace QRest
{
	namespace QWrapper
	{
		class QFridgeParameters
		{
			public:
				QFridgeParameters();
				QFridgeParameters(std::string, QFridgeTemperature);

				std::string cooldownDate;
				QFridgeTemperature temperature;
		};
	}
}

#endif