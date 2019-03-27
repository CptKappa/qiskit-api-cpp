#ifndef QMULTIQUBITGATES_H_INCLUDED__
#define QMULTIQUBITGATES_H_INCLUDED__
#include <string>
#include <list>
#include "QGateError.h"

namespace QRest
{
	namespace QWrapper
	{
		class QMultiQubitGates
		{
		public:
			QMultiQubitGates();
			QMultiQubitGates(std::list<int>, std::string, QGateError, std::string);

			std::list<int> qubits;
			std::string type;
			QGateError gateError;
			std::string name;
		};
	}
}

#endif