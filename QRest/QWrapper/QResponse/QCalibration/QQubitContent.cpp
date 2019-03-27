#ifndef QQUBITCONTENT_CPP_INCLUDED
#define QQUBITCONTENT_CPP_INCLUDED

#include "QQubitContent.h"

namespace QRest
{
	namespace QWrapper
	{
		QQubitContent::QQubitContent()
		{

		}

		QQubitContent::QQubitContent(std::string date, double value)
		{
			this->date = date;
			this->value = value;
		}

		QQubitContent::QQubitContent(std::string date, double value, std::string unit)
		{
			this->date = date;
			this->value = value;
			this->unit = unit;
		}
	}
}

#endif