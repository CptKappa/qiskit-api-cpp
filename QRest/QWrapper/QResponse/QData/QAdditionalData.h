#ifndef QADDITIONALDATA_H_INCLUDED__
#define QADDITIONALDATA_H_INCLUDED__

#include <string>
#include <list>

namespace QRest
{
	namespace QWrapper
	{
		class QAdditionalData
		{
		public:
			QAdditionalData();
			QAdditionalData(std::string);
			std::string seed;
		};
	}
}

#endif