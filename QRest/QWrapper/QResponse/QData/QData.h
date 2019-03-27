#ifndef QDATA_H_INCLUDED__
#define QDATA_H_INCLUDED__

#include <string>
#include "QDataP.h"
#include "QAdditionalData.h"

namespace QRest
{
	namespace QWrapper
	{
		class QData
		{
			public:
				QData();
				QData(QDataP, std::string, std::string, double);
				QData(std::string, QDataP, QAdditionalData, std::string, std::string, double);

				std::string creg_labels;
				QDataP p;
				QAdditionalData additionalData;
				std::string qasm;
				std::string serialNumberDevice;
				double time;
		};
	}
}

#endif