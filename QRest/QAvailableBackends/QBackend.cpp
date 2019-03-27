// Copyright by Benjamin Luxbacher

#include "QBackend.h"

namespace QRest
{
    namespace QAvailableBackends
    {
        QBackend::QBackend()
        {
            
        }

        QBackend::QBackend(std::string id, std::string name)
        {
            this->id = id;
            this->name = name;
        }

        QBackend::QBackend(
            std::string name, 
            std::string version, 
            std::string status, 
            std::string serialNumber, 
            std::string description, 
            std::string basisGates, 
            std::string onlineDate, 
            std::string chipName, 
            bool deleted, 
            std::string id, 
            std::string topologyId, 
            std::string url, 
            std::string internalId, 
            bool simulator, 
            bool allowQObject, 
            int nQubits, 
            std::list<std::tuple<int, int>> couplingMap
        )
        {
            this->name = name;
            this->version = version;
            this->status = status;
            this->serialNumber = serialNumber;
            this->description = description;
            this->basisGates = basisGates;
            this->onlineDate = onlineDate;
            this->chipName = chipName;
            this->deleted = deleted;
            this->id = id;
            this->topologyId = topologyId;
            this->url = url;
            this->internalId = internalId;
            this->simulator = simulator;
            this->allowQObject = allowQObject;
            this->nQubits = nQubits;
            this->couplingMap = couplingMap;
        }

        QBackend::~QBackend()
        {

        }
    }
}