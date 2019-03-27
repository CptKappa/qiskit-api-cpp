#ifndef QDATA_CPP_INCLUDED
#define QDATA_CPP_INCLUDED

#include "QData.h"

namespace QRest
{
	namespace QWrapper
	{
		QData::QData()
		{

		}

		QData::QData(QDataP p, std::string qasm, std::string serialNumberDevice, double time)
		{
			this->p = p;
			this->qasm = qasm;
			this->serialNumberDevice = serialNumberDevice;
			this->time = time;
		}

		QData::QData(std::string creg_labels, QDataP p, QAdditionalData additionalData, std::string qasm, std::string serialNumberDevice, double time)
		{
			this->creg_labels = creg_labels;
			this->p = p;
			this->additionalData = additionalData;
			this->qasm = qasm;
			this->serialNumberDevice = serialNumberDevice;
			this->time = time;
		}
	}
}

#endif