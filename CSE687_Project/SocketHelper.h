#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "ThreadManager.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "1234"

class SocketHelper
{
public:
	int Receive(ThreadManager& acTM);
	int Send(std::vector<std::string>& resultVector);

	struct ConnectionInfo
	{
		// TO DO, add IP information 
	};

	ConnectionInfo CI;
};

