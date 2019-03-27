#ifndef QMEASURECREG_CPP_INCLUDED
#define QMEASURECREG_CPP_INCLUDED

#include "QMeasureCreg.h"

namespace QRest
{
	namespace QWrapper
	{
		QMeasureCreg::QMeasureCreg()
		{
		}

		QMeasureCreg::QMeasureCreg(int line, int bit)
		{
			this->line = line;
			this->bit = bit;
		}
	}
}

#endif