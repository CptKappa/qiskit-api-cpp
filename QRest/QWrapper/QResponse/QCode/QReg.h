#ifndef QREG_H_INCLUDED__
#define QREG_H_INCLUDED__

#include <string>

namespace QRest
{
	namespace QWrapper
	{
		class QReg
		{
			public:
				QReg();
				QReg(std::string, int);
				std::string name;
				int size;
		};
	}
}

#endif