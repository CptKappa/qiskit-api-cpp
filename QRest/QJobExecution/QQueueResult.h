// Copyright by Benjamin Luxbacher

#ifndef _QRESULT_H_
#define _QRESULT_H_

#include <list>

#include "QExecution.h"
#include "../QAvailableBackends/QBackend.h"
#include "QInfoQueue.h"

namespace QRest
{
    namespace QJobExecution
    {
        class QQueueResult
        {
        private:

        public:
            QQueueResult();
            QQueueResult(
                std::list<QExecution> qasms, 
                int shots, 
                QAvailableBackends::QBackend backend, 
                std::string status, 
                int maxCredits, 
                int usedCredits, 
                std::string creationDate, 
                std::string id, 
                std::string userId, 
                QInfoQueue infoQueue, 
                std::string json
            );
            
            ~QQueueResult();

            std::list<QExecution> qasms;
            int shots;
            QAvailableBackends::QBackend backend;
            std::string status;
            int maxCredits;
            int usedCredits;
            std::string creationDate;
            std::string id;
            std::string userId;
            QInfoQueue infoQueue;

            std::string json;
        };
    }
}

#endif