#ifndef SERVER_EVENT_INFC_H
#define SERVER_EVENT_INFC_H

#include "ServerGatewayInfc.h"

namespace town {

class ServerEventInfc;
using ServerEventInfcPtr = std::shared_ptr<ServerEventInfc>;

class ServerEventInfc
{
public:
	static ServerEventInfcPtr GetInstance();
	int32_t Initialization(int32_t iPort, ServerGatewayInfcPtr pServerGatewayInfc);
	void StartServer();

protected:
	ServerEventInfc();
	~ServerEventInfc();
};

} /* town */

#endif /* SERVER_EVENT_INFC_H */