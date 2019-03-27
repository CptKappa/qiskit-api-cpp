#ifndef QJSONQASM_H_INCLUDED__
#define QJSONQASM_H_INCLUDED__

#include <string>
#include <list>
#include "QTopology.h"
#include "QPlayground.h"

namespace QRest
{
	namespace QWrapper
	{
        class QJsonQASM
        {
            public:
                QJsonQASM();
                QJsonQASM(std::string, QTopology, std::list<QPlayground>,int,bool,int,std::string);
                
                std::string gateDefinitions;
                QTopology topology;
                std::list<QPlayground> playground;
                int numberGates;
                bool hasMeasures;
                int numberColumns;
                std::string include;
        };
    }
}

#endif