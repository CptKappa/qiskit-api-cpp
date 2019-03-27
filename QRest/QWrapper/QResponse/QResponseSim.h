#ifndef QRESPONSESIM_H_INCLUDED__
#define QRESPONSESIM_H_INCLUDED__

#include "QResponse.h"
#include "QCode/QCode.h"

namespace QRest
{
	namespace QWrapper
	{
		class QResponseSim : public QResponse
		{
			public:
				QResponseSim();
				QResponseSim(
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
				);

				QCode code;
				QParamsCustomize paramsCustomize;
				double time;
				std::string deviceRunType;
				std::string codeId;

		};
	}
}

#endif