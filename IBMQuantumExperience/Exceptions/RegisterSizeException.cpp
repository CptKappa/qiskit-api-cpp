#include "RegisterSizeException.h"

RegisterSizeException::RegisterSizeException(std::string usr_msg, std::string dev_msg)
	: ApiException(usr_msg, dev_msg) { }