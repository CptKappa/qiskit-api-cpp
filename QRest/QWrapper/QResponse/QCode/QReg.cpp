#ifndef QREG_CPP_INCLUDED
#define QREG_CPP_INCLUDED

#include "QReg.h"

namespace QRest
{
	namespace QWrapper
	{
		QReg::QReg()
		{

		}

		QReg::QReg(std::string name, int size)
		{
			this->name = name;
			this->size = size;
		}
	}
}

#endif