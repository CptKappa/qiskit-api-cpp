#ifndef QRESPONSEREAL_CPP_INCLUDED
#define QRESPONSEREAL_CPP_INCLUDED

#include "QResponseReal.h"

namespace QRest
{
	namespace QWrapper
	{
		QResponseReal::QResponseReal()
		{

		}

		QResponseReal::QResponseReal(
			std::string startDate
			, long modificationDate
			, int shots
			, bool deleted
			, bool userDeleted
			, std::string userId
			, std::string jobId
			, std::string qasm
			, std::string endDate
			, std::string id
			, std::string deviceId
			, QResult result
			, QStatus status
			, QIP ip
			, QCalibration calibration
			, std::string typeCredits
		) 
			: QResponse(startDate, modificationDate, shots, deleted, userDeleted, userId, qasm, endDate, id, deviceId, result, status, ip)
		{
			this->calibration = calibration;
			this->typeCredits = typeCredits;
			this->jobId = jobId;
		}

		QResponseReal::QResponseReal(
			std::string startDate
			, long modificationDate
			, int shots
			, bool deleted
			, bool userDeleted
			, std::string userId
			, std::string jobId
			, std::string qasm
			, std::string id
			, QStatus status
			, QIP ip
			, std::string typeCredits
		)
			: QResponse(startDate, modificationDate, shots, deleted, userDeleted, userId, qasm, id, status, ip)
		{
			this->typeCredits = typeCredits;
			this->jobId = jobId;
		}
	}
}

#endif