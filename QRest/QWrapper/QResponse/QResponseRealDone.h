#ifndef QRESPONSEREALDONE_H_INCLUDED__
#define QRESPONSEREALDONE_H_INCLUDED__

#include "QResponseReal.h"

namespace QRest
{
	namespace QWrapper
	{
		class QResponseRealDone : public QResponseReal
		{
			public:
				QResponseRealDone();
				QResponseRealDone(
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
					, double time
				);
				
				double time;
		};
	}
}

#endif