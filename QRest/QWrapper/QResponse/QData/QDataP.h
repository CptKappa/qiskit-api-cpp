#ifndef QDATAP_H_INCLUDED__
#define QDATAP_H_INCLUDED__

#include <string>
#include <list>

namespace QRest
{
	namespace QWrapper
	{
		class QDataP
		{
		public:
			QDataP();
			QDataP(std::list<std::string>, std::list<double>);
			QDataP(std::list<int>, std::list<std::string>, std::list<double>);

			std::list<std::string> labels;
			std::list<double> values;
			std::list<int> qubits;
		};
	}
}

#endif