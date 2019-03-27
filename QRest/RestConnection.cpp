// Copyright by Benjamin Luxbacher

#include "RestConnection.h"

namespace QRest
{
    QConnection::QConnection(std::string apiToken)
    {
        this->apiToken = apiToken;
    }

    QConnection::~QConnection()
    {

    }

	static size_t writer(char* data, size_t size, size_t nmemb, std::ostringstream* stream)
	{
		size_t count = size * nmemb;

		stream->write(data, count);

		return count;
	}

    std::string QConnection::Get(std::string url, std::string getparams, long* statuscode)
	{
        struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");
		headers = curl_slist_append(headers, (std::string("x-qx-client-application: ") +  client_application).c_str());

		CURL* curl = curl_easy_init();

		if (curl)
		{
			std::ostringstream contentStream;

			curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &contentStream);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);

			curl_easy_setopt(curl, CURLOPT_URL, (url + "?" + getparams).c_str());
			CURLcode curlRes = curl_easy_perform(curl);

			if (curlRes != CURLE_OK)
			{
				curl_easy_cleanup(curl);
				throw Exceptions::WebRequestException(curl_easy_strerror(curlRes));
			}

			if (statuscode)
			{
				curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, statuscode);
			}

			std::string content = contentStream.str();

			curl_easy_cleanup(curl);

			return content;
		}
		else
		{
			throw Exceptions::WebRequestException("Curl has not been initialized");
		}
	}

    std::string QConnection::Post(std::string url, std::string postparams, long* statuscode)
	{
        struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");
		headers = curl_slist_append(headers, (std::string("x-qx-client-application: ") +  client_application).c_str());

		CURL* curl = curl_easy_init();

		if (curl)
		{
			std::ostringstream contentStream;

			curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &contentStream);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);

			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postparams.c_str());
			CURLcode curlRes = curl_easy_perform(curl);

			if (curlRes != CURLE_OK)
			{
				curl_easy_cleanup(curl);
				throw Exceptions::WebRequestException(curl_easy_strerror(curlRes));
			}

			if (statuscode)
			{
				curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, statuscode);
			}

			std::string content = contentStream.str();

			curl_easy_cleanup(curl);

			return content;
		}
		else
		{
			throw Exceptions::WebRequestException("Curl has not been initialized");
		}
	}

    void QConnection::Login()
    {
		std::string data = "{ \"apiToken\" : \"" + this->apiToken + "\" }";

		long response_code;

		try
		{
			std::string response = Post(std::string(url) + "/users/loginWithToken", data, &response_code);
			
			Json::Reader jsonReader;
			Json::Value jsonObj;

			jsonReader.parse(response, jsonObj);

			if (response_code == 401)
			{
				// For 401: ACCEPT_LICENSE_REQUIRED, a detailed message is
				// present in the response and passed to the exception.

				const char* error_msg = jsonObj["error"]["message"].asCString();

				if (error_msg)
				{
					throw Exceptions::WebRequestException(std::string("error during login: ") + error_msg);
                    return;
				}
				else
				{
					throw Exceptions::WebRequestException("invalid token");
                    return;
				}
			}

			// 200 = http-ok
			if (response_code == 200)
			{
				// ToDo: improve?
				if (jsonObj["id"] == Json::nullValue || 
					jsonObj["ttl"] == Json::nullValue ||
					jsonObj["created"] == Json::nullValue ||
					jsonObj["userId"] == Json::nullValue)
				{
					throw Exceptions::WebRequestException(std::string("Missing response values") + "id: " + jsonObj["id"].asString() + ", ttl: " + jsonObj["ttl"].asString() + ", created: " + jsonObj["created"].asString() + ", userId: " + jsonObj["userId"].asString());
				    return;
                }

				//std::cout << content << std::endl;

				// save response data
				this->accessToken = jsonObj["id"].asString();
				this->ttl = jsonObj["ttl"].asInt();
				this->created = jsonObj["created"].asString();
				this->userId = jsonObj["userId"].asString();
			}
			else
			{
				throw Exceptions::WebRequestException("HTTP-CODE " + std::to_string(response_code));
                return;
			}
		}
		catch (const QRest::Exceptions::WebRequestException& e)
		{
			std::cerr << "error during login: " << e.what() << std::endl;
			throw e;
		}
    }

    QJobExecution::QQueueResult QConnection::RunJob(std::string qasm, std::string backend, int shots, int maxCredits, std::string name)
    {
		QJobExecution::QQueueResult res = QJobExecution::QQueueResult();

		// get backend info
		// get max qubits
		// append include & regs
		// include \"qelib1.inc\";\nqreg q[16];\ncreg c[3];\n\n

		//std::string code = R"(include \"qelib1.inc\";\nqreg q[16];\ncreg c[3];\n)" + qasm;

		std::string experimentName;
		long response_code;

		// set experiment name
        if (!name.empty())
        {
            experimentName = name;
        }
        else
        {
			/*
			// TODO: time in not correct
            // %Y%m%d%H%M%S
            time_t tt;
            time(&tt);
            tm* t = localtime(&tt);

            experimentName = std::string("Experiment #") + 
                std::to_string(t->tm_year) + 
                std::to_string(t->tm_mon) + 
                std::to_string(t->tm_yday) + 
                std::to_string(t->tm_hour) + 
                std::to_string(t->tm_min) + 
                std::to_string(t->tm_sec);
			*/

			experimentName = "unnamed";
        }

		// set post variables as json
		std::string data = std::string("{ ") + 
			"\"name\" : \"" + experimentName + "\", " + 
			//"\"codeType\" : \"" + this->codeType + "\", " + 
			"\"maxCredits\" : " + std::to_string(maxCredits) + ", " + 
			"\"shots\" : " + std::to_string(shots) + ", " + 
			"\"backend\" : { \"name\" : \"" + backend + "\" }" + ", " + 
            "\"qasms\" : [{ \"qasm\" : \"" + qasm + "\" }]" + 
            " }";

		//std::cout << std::endl << std::endl << data << std::endl << std::endl << std::endl;

		// set url and get variables
        std::string executeUrl = std::string(url) + 
            "/jobs?access_token=" + this->accessToken;

		try
		{
			std::string response = Post(executeUrl, data, &response_code);
			
			Json::Reader jsonReader;
			Json::Value jsonObj;

			jsonReader.parse(response, jsonObj);

			// 200 = http-ok
			if (response_code == 200)
			{
				// save response data

				std::list<QJobExecution::QExecution> qasms;

				for(Json::Value qasm : jsonObj["qasms"])
				{
					qasms.push_back(QJobExecution::QExecution(qasm["qasm"].asString(), qasm["status"].asString(), qasm["executionId"].asString()));
				}

				QAvailableBackends::QBackend backend = QAvailableBackends::QBackend(
					jsonObj["backend"]["id"].asString(), 
					jsonObj["backend"]["name"].asString()
				);

				QJobExecution::QInfoQueue infoQueue = QJobExecution::QInfoQueue(
					jsonObj["infoQueue"]["status"].asString(), 
					jsonObj["infoQueue"]["position"].asInt()
				);

				res = QJobExecution::QQueueResult(
					qasms, 
					jsonObj["shots"].asInt(), 
					backend, 
					jsonObj["status"].asString(), 
					jsonObj["maxCredits"].asInt(), 
					jsonObj["usedCredits"].asInt(), 
					jsonObj["creationDate"].asString(), 
					jsonObj["id"].asString(), 
					jsonObj["userId"].asString(), 
					infoQueue, 
					response
				);
			}
			else
			{
				std::cout << "ERROR" << std::endl;
				throw Exceptions::WebRequestException("HTTP-CODE: " + std::to_string(response_code));
			}
		}
		catch (const QRest::Exceptions::WebRequestException& e)
		{
			std::cerr << "error during job execution: " << e.what();
			throw e;
		}

		return res;
    }

	QWrapper::QResponse* QConnection::GetResultFromExecution(std::string executionId)
	{
		QJobExecution::QQueueResult res = QJobExecution::QQueueResult();

		// set url and get variables
        std::string executeUrl = std::string(url) + 
            "/Executions/" + executionId;

		std::string getparams = "access_token=" + this->accessToken;

		long response_code;

		try
		{
			std::string response = Get(executeUrl, getparams, &response_code);

			Json::Reader jsonReader;
			Json::Value jsonObj;

			jsonReader.parse(response, jsonObj);

			// 200 = http-ok
			if (response_code == 200)
			{
				// save response data

				QWrapper::QResponse* qresponse = QWrapper::QWFactory::Create(response);
				
				return qresponse;
			}
			else
			{
				throw Exceptions::WebRequestException("HTTP-CODE " + std::to_string(response_code));
			}
		}
		catch (const QRest::Exceptions::WebRequestException& e)
		{
			std::cerr << "error during result request: " << e.what() << std::endl;
			throw e;
		}
	}

	std::vector<QAvailableBackends::QBackend> QConnection::AvailableBackends()
	{
		std::vector<QAvailableBackends::QBackend> res = std::vector<QAvailableBackends::QBackend>();

		// set url and get variables
        std::string executeUrl = std::string(url) + "/backends";
		std::string getparams = "access_token=" + this->accessToken;

		long response_code;
		
		try
		{
			std::string response = Get(executeUrl, getparams, &response_code);

			Json::Reader jsonReader;
			Json::Value jsonObj;

			jsonReader.parse(response, jsonObj);

			// 200 = http-ok
			if (response_code == 200)
			{
				// save response data

				for(Json::Value backend : jsonObj)
				{
					std::list<std::tuple<int, int>> couplingMap;

					for(Json::Value couple : backend["couplingMap"])
					{
						couplingMap.push_back(std::tuple<int, int>(couple[0].asInt(), couple[1].asInt()));
					}

					res.push_back(QAvailableBackends::QBackend(
						backend["name"].asString(), 
						backend["version"].asString(), 
						backend["status"].asString(), 
						backend["serialNumber"].asString(),
						backend["description"].asString(), 
						backend["basisGates"].asString(), 
						backend["onlineDate"].asString(), 
						backend["chipName"].asString(), 
						backend["deleted"].asBool(), 
						backend["id"].asString(), 
						backend["topologyId"].asString(), 
						backend["url"].asString(), 
						backend["internalId"].asString(), 
						backend["simulator"].asBool(), 
						backend["allowQObject"].asBool(), 
						backend["nQubits"].asInt(), 
						couplingMap
					));
				}
			}
			else
			{
				throw Exceptions::WebRequestException("HTTP-CODE " + std::to_string(response_code));
				return res;
			}
		}
		catch (const QRest::Exceptions::WebRequestException& e)
		{
			std::cerr << "error during backends request: " << e.what() << std::endl;
			throw e;
		}

		return res;
	}
}