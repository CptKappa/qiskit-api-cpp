// Copyright by Benjamin Luxbacher

#ifndef _WEBREQUESTEXCEPTION_H_
#define _WEBREQUESTEXCEPTION_H_

#include <string>
#include <exception>

namespace QRest
{
	namespace Exceptions
    {
        class WebRequestException : public std::exception
        {
        private:
            std::string message;
            std::exception* innerException;

        public:
            explicit WebRequestException();
            explicit WebRequestException(std::string message);
            explicit WebRequestException(std::string message, std::exception* innerException);
		    const char* what() const throw();
            const std::exception* GetInnerException() const throw();
        };
    }
}

#endif