#ifndef QRESPONSEREALUNDONE_CPP_INCLUDED
#define QRESPONSEREALUNDONE_CPP_INCLUDED

#include "QResponseRealUndone.h"

namespace QRest
{
	namespace QWrapper
	{
		QResponseRealUndone::QResponseRealUndone(
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
		) : QResponseReal(startDate, modificationDate, shots, deleted, userDeleted, userId, jobId, qasm, id, status, ip, typeCredits) 
		{

		}
	}
}

#endif
