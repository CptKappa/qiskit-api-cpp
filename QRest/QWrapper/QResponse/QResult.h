#ifndef QRESULT_H_INCLUDED__
#define QRESULT_H_INCLUDED__

#include <string>
#include "QData/QData.h"

namespace QRest
{
	namespace QWrapper
	{
		class QResult
		{
		public:
			QResult();
			QResult(std::string, QData);
			
			std::string date;
			QData data;
		};
	}
}

#endif