#ifndef QCODE_CPP_INCLUDED
#define QCODE_CPP_INCLUDED

#include "QCode.h"

namespace QRest
{
	namespace QWrapper
	{
		QCode::QCode()
		{

		}

		QCode::QCode(std::string type, bool active, int versionId, std::string idCode, std::string name, QJsonQASM jsonQASM, std::string qasm, std::string codeType, std::string creationDate, bool deleted, long orderDate, bool userDeleted, bool isPublic, std::string id, std::string userId)
		{
			this->type = type;
			this->active = active;
			this->versionId = versionId;
			this->idCode = idCode;
			this->name = name;
			this->jsonQASM = jsonQASM;
			this->qasm = qasm;
			this->codeType = codeType;
			this->creationDate = creationDate;
			this->deleted = deleted;
			this->orderDate = orderDate;
			this->userDeleted = userDeleted;
			this->isPublic = isPublic;
			this->id = id;
			this->userId = userId;
		}
	}
}

#endif