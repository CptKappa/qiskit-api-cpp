#ifndef QRESPONSE_H_INCLUDED__
#define QRESPONSE_H_INCLUDED__
#include <string>
#include "QResult.h"
#include "QStatus.h"
#include "QIP.h"
#include "QCalibration/QCalibration.h"
#include "QParamsCustomize.h"
#include "QCode/QCode.h"

namespace QRest
{
	namespace QWrapper
	{
		class QResponse
		{

			public:
				QResponse();
				QResponse(
					std::string startDate
					, long modificationDate
					, int shots
					, bool deleted
					, bool userDeleted
					, std::string userId
					, std::string qasm
					, std::string endDate
					, std::string id
					, std::string deviceId
					, QResult result
					, QStatus status
					, QIP ip
				);

				// Constructor for UndoneResponse
				QResponse(
					std::string startDate
					, long modificationDate
					, int shots
					, bool deleted
					, bool userDeleted
					, std::string userId
					, std::string qasm
					, std::string id
					, QStatus status
					, QIP ip
				);

				std::string startDate;
				long modificationDate;
				int shots;
				bool deleted;
				bool userDeleted;
				std::string userId;
				std::string qasm;
				std::string endDate;
				std::string id;
				std::string deviceId;
				QResult result;
				QStatus status;
				QIP ip;
		};
	}
}

#endif