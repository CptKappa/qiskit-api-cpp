#ifndef QJSONQASM_CPP_INCLUDED
#define QJSONQASM_CPP_INCLUDED

#include "QJsonQASM.h"

namespace QRest
{
	namespace QWrapper
	{
		QJsonQASM::QJsonQASM()
		{

		}

		QJsonQASM::QJsonQASM(std::string gateDefinitions, QTopology topology, std::list<QPlayground> playground, int numberGates, bool hasMeasure, int numberColumns, std::string include)
		{
			this->gateDefinitions = gateDefinitions;
			this->topology = topology;
			this->playground = playground;
			this->numberGates = numberGates;
			this->hasMeasures = hasMeasure;
			this->numberColumns = numberColumns;
			this->include = include;
		}
	}
}

#endif