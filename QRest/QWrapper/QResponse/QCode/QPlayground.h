#ifndef QPLAYGROUND_H_INCLUDED__
#define QPLAYGROUND_H_INCLUDED__

#include <string>
#include <list>
#include "QGate.h"

namespace QRest
{
	namespace QWrapper
	{
		class QPlayground
		{
			public:
				QPlayground();
				QPlayground(std::string, int, std::list<QGate>);

				std::string name;
				int line;
				std::list<QGate> gates;
			};
	}
}
#endif