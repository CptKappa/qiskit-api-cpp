// Copyright by Benjamin Luxbacher

#ifndef _RESTCONNECTION_H_
#define _RESTCONNECTION_H_

#include <stdio.h>
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include "QJobExecution/QQueueResult.h"
#include "Exceptions/WebRequestException.h"
#include "QWrapper/QWFactory.h"

namespace QRest
{
    class QConnection
    {
    private:
        std::string apiToken;
        std::string accessToken;
        int ttl;
        std::string created;
        std::string userId;

        const std::string client_application = "C++_API";
        const std::string codeType = "QASM2";
        std::string url = "https://quantumexperience.ng.bluemix.net/api";

    public:
        QConnection(std::string apiToken);
        ~QConnection();

        void Login();

        QJobExecution::QQueueResult RunJob(std::string qasm, std::string backend, int shots, int maxCredits, std::string name);
        QWrapper::QResponse* GetResultFromExecution(std::string executionId);
        std::vector<QAvailableBackends::QBackend> AvailableBackends();

    private:
        // getparams: "access_token=" + this->accessToken
        std::string Get(std::string url, std::string getparams, long* statuscode);
        // postparams: { \"apiToken\" : \"" + this->apiToken + "\" }
        std::string Post(std::string url, std::string postparams, long* statuscode);
    };
}

#endif
