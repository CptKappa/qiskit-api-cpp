#ifndef QGATE_CPP_INCLUDED
#define QGATE_CPP_INCLUDED

#include "QGate.h"

namespace QRest
{
	namespace QWrapper
	{
		QGate::QGate()
		{

		}

		QGate::QGate(std::string name, std::string qasm, int position, std::list<bool> affectedLines, QMeasureCreg measureCreg)
		{
			this->name = name;
			this->qasm = qasm;
			this->position = position;
			this->affectedLines = affectedLines;
			this->measureCreg = measureCreg;
		}
	}
}

#endif