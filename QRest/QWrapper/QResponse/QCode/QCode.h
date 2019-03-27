#ifndef QCODE_H_INCLUDED__
#define QCODE_H_INCLUDED__

#include <string>
#include "QJsonQASM.h"

namespace QRest
{
	namespace QWrapper
	{
		class QCode
		{
			public:
				QCode();
				QCode(std::string, bool, int, std::string, std::string, QJsonQASM, std::string, std::string, std::string, bool, long, bool, bool, std::string, std::string);
			
				std::string type;
				bool active;
				int versionId;
				std::string idCode;
				std::string name;
				QJsonQASM jsonQASM;
				std::string qasm;
				std::string codeType;
				std::string creationDate;
				bool deleted;
				long orderDate;
				bool userDeleted;
				bool isPublic;
				std::string id;
				std::string userId;
		};
	}
}

#endif