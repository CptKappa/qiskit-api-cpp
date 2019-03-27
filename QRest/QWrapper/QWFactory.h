#ifndef QWFACTORY_CPP_INCLUDED
#define QWFACTORY_CPP_INCLUDED

#include "QResponse/QResponse.h"
#include "QResponse/QResponseRealUndone.h"
#include "QResponse/QResponseRealDone.h"
#include "QResponse/QResponseSim.h"
#include <jsoncpp/json/json.h>
#include <string>

#define STATUD_ID_DONE "DONE"
#define STATUD_ID_WORKING "WORKING_IN_PROGRESS"
// Fehlt in QWFactory.cpp --> exisitiert nur in responseReal.json
#define STATUS_ID_RUNNING "RUNNING"

namespace QRest
{
	namespace QWrapper
	{
		class QWFactory
		{

		public:
			QWFactory() = delete;
			static QResponse* Create(std::string str);
		};
	}
}

#endif