#include "socket.hpp"

void Socket::SetForcedResponse(http_status_code_t code){
	this->_forcedresponse = true;
	this->_forcedstatus = code;
}
