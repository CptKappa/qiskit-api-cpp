#ifndef QSTATUS_CPP_INCLUDED
#define QSTATUS_CPP_INCLUDED

#include "QStatus.h"

namespace QRest
{
	namespace QWrapper
	{
		QStatus::QStatus()
		{
			
		}

		QStatus::QStatus(std::string id)
		{
			this->id = id;
		}
	}
}

#endif