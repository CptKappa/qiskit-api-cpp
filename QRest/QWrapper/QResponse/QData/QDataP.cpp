#ifndef QDATAP_CPP_INCLUDED
#define QDATAP_CPP_INCLUDED

#include "QDataP.h"

namespace QRest
{
	namespace QWrapper
	{
		QDataP::QDataP()
		{

		}

		QDataP::QDataP(std::list<std::string> labels, std::list<double> values)
		{
			this->labels = labels;
			this->values = values;
		}

		QDataP::QDataP(std::list<int> qubits, std::list<std::string> labels, std::list<double> values)
		{
			this->qubits = qubits;
			this->labels = labels;
			this->values = values;
		}
	}
}

#endif