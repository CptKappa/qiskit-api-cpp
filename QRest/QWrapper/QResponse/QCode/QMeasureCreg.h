#ifndef QMEASURECREG_H_INCLUDED__
#define QMEASURECREG_H_INCLUDED__

namespace QRest
{
	namespace QWrapper
	{
		class QMeasureCreg
		{
			public:
				QMeasureCreg();
				QMeasureCreg(int, int);
				int line;
				int bit;
		};
	}
}

#endif