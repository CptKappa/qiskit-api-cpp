#ifndef QTOPOLOGY_CPP_INCLUDED
#define QTOPOLOGY_CPP_INCLUDED

#include "QTopology.h"

namespace QRest
{
	namespace QWrapper
	{
		QTopology::QTopology()
		{

		}

		QTopology::QTopology(std::list<QReg> cregs, std::list<QReg> qregs, std::string qasmHeader)
		{
			this->cregs = cregs;
			this->qregs = qregs;
			this->qasmHeader = qasmHeader;
		}
	}
}

#endif