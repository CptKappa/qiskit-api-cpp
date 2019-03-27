#ifndef QSTATUS_H_INCLUDED
#define QSTATUS_H_INCLUDED

#include <string>

namespace QRest
{
	namespace QWrapper
	{
		class QStatus
		{
		public:
			QStatus();
			QStatus(std::string);
			std::string id;
		};
	}
}

#endif // !QSTATUS_H_INCLUDED
