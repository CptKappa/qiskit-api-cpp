#ifndef QPLAYGROUND_CPP_INCLUDED
#define QPLAYGROUND_CPP_INCLUDED

#include "QPlayground.h"

namespace QRest
{
	namespace QWrapper
	{
		QPlayground::QPlayground()
		{

		}

		QPlayground::QPlayground(std::string name, int line, std::list<QGate> gates)
		{
			this->name = name;
			this->line = line;
			this->gates = gates;
		}
	}
}

#endif