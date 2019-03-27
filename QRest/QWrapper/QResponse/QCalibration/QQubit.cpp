#ifndef QQUBIT_CPP_INCLUDED
#define QQUBIT_CPP_INCLUDED

#include "QQubit.h"

namespace QRest
{
	namespace QWrapper
	{
		QQubit::QQubit()
		{

		}

		QQubit::QQubit(std::string name, QQubitContent buffer, QQubitContent gateTime, QQubitContent T2, QQubitContent T1, QQubitContent frequency, QQubitContent gateError, QQubitContent readoutError)
		{
			this->name = name;
			this->buffer = buffer;
			this->gateTime = gateTime;
			this->T2 = T2;
			this->T1 = T1;
			this->frequency = frequency;
			this->gateError = gateError;
			this->readoutError = readoutError;
		}
	}
}

#endif