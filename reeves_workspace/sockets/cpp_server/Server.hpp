#include <iostream>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Server{
	
public:
	
	Server(void) = default;
	
	virtual ~Server() = default;
	
};