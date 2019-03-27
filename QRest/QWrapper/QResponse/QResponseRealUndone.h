#ifndef QRESPONSEREALUNDONE_H_INCLUDED__
#define QRESPONSEREALUNDONE_H_INCLUDED__

#include "QResponseReal.h"

namespace QRest
{
	namespace QWrapper
	{
		class QResponseRealUndone : public QResponseReal
		{
			public:
				// startDate, modDate, typeCred, status, ip, shots, deleted, userDeleted, id, userId, jobId, qasm

				QResponseRealUndone(
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
		};
	}
}

#endif