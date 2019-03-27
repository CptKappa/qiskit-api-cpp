#ifndef QRESPONSEREAL_H_INCLUDED__
#define QRESPONSEREAL_H_INCLUDED__

#include "QResponse.h"

namespace QRest
{
	namespace QWrapper
	{
		class QResponseReal : public QResponse
		{
			public:
				QResponseReal();
				QResponseReal(
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
				);

				// Constructor for undone response
				QResponseReal(
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
				);

				QCalibration calibration;
				std::string typeCredits;
				std::string jobId;
		};
	}
}

#endif