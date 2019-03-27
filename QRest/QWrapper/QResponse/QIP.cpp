#ifndef QIP_CPP_INCLUDED
#define QIP_CPP_INCLUDED

#include "QIP.h"
namespace QRest
{
	namespace QWrapper
	{
		QIP::QIP()
		{

		}

		QIP::QIP(std::string ip, std::string country, std::string continent)
		{
			this->ip = ip;
			this->country = country;
			this->continent = continent;
		}
	}
}

#endif