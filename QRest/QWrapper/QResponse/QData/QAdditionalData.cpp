#ifndef QADDITIONALDATA_CPP_INCLUDED
#define QADDITIONALDATA_CPP_INCLUDED

#include "QAdditionalData.h"

namespace QRest
{
	namespace QWrapper
	{
		QAdditionalData::QAdditionalData()
		{

		}

		QAdditionalData::QAdditionalData(std::string seed)
		{
			this->seed = seed;
		}
	}
}

#endif