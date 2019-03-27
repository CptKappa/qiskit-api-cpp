#ifndef QTOPOLOGY_H_INCLUDED__
#define QTOPOLOGY_H_INCLUDED__

#include <string>
#include <list>
#include "QReg.h"

namespace QRest
{
	namespace QWrapper
	{
		class QTopology
		{
			public:
				QTopology();
				QTopology(std::list<QReg>, std::list<QReg>, std::string);

				std::list<QReg> cregs;
				std::list<QReg> qregs;
				std::string qasmHeader;
		};
	}
}

#endif