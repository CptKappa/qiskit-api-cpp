#ifndef QQUBIT_H_INCLUDED__
#define QQUBIT_H_INCLUDED__
#include <string>
#include "QQubitContent.h"

namespace QRest
{
	namespace QWrapper
	{
		class QQubit
		{
		public:
			QQubit();
			QQubit(std::string, QQubitContent, QQubitContent, QQubitContent, QQubitContent, QQubitContent, QQubitContent, QQubitContent);

			std::string name;
			QQubitContent buffer;
			QQubitContent gateTime;
			QQubitContent T2;
			QQubitContent T1;
			QQubitContent frequency;
			QQubitContent gateError;
			QQubitContent readoutError;
		};
	}
}

#endif