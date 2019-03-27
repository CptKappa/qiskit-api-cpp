#ifndef QRESPONSESIM_CPP_INCLUDED
#define QRESPONSESIM_CPP_INCLUDED

#include "QResponseSim.h"

namespace QRest
{
	namespace QWrapper
	{
		QResponseSim::QResponseSim()
		{

		}

		QResponseSim::QResponseSim(
			QCode code
			, QParamsCustomize paramsCustomize
			, double time
			, std::string deviceRunType
			, std::string startDate
			, long modificationDate
			, int shots
			, bool deleted
			, bool userDeleted
			, std::string userId
			, std::string qasm
			, std::string endDate
			, std::string id
			, std::string deviceId
			, std::string codeId
			, QResult result
			, QStatus status
			, QIP ip
		)
			: QResponse(startDate, modificationDate, shots, deleted, userDeleted, userId, qasm, endDate, id, deviceId, result, status, ip) {
			this->code = code;
			this->paramsCustomize = paramsCustomize;
			this->time = time;
			this->deviceRunType = deviceRunType;
			this->codeId = codeId;
		}
	}
}

#endif