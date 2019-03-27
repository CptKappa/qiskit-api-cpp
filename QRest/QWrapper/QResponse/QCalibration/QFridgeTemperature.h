#ifndef QFRIDGETEMPERATURE_H_INCLUDED__
#define QFRIDGETEMPERATURE_H_INCLUDED__
#include <string>
#include <list>

namespace QRest
{
	namespace QWrapper
	{
		class QFridgeTemperature
		{
		public:
			QFridgeTemperature();
			QFridgeTemperature(std::string, std::list<std::string>, std::string);

			std::string date;
			std::list<std::string> value;
			std::string unit;
		};
	}
}

#endif