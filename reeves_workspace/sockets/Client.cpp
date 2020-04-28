#include <iostream>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
  
int main(int argc, char *argv[])
{
    if (argc > 1 && *(argv[1]) == '-')
    {
        exit(1);
    }
 
    // Create socket
    int s0 = socket(AF_INET, SOCK_STREAM, 0);
    if (s0 < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }
 
    // Fill in server IP address
    struct sockaddr_in server;
    int serverAddrLen;
    bzero( &server, sizeof( server ) );
 
 
    const char* peerHost = "localhost";
    if (argc > 1)
        peerHost = argv[1];
 
    // Resolve server address (convert from symbolic name to IP number)
    struct hostent *host = gethostbyname(peerHost);
    if (host == NULL)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }
 
    server.sin_family = AF_INET;
    short peerPort = 1234;
    if (argc >= 3)
        peerPort = (short) atoi(argv[2]);
    server.sin_port = htons(peerPort);
 
    // Print a resolved address of server (the first IP of the host)
    std::cout << "server address = " << (host->h_addr_list[0][0] & 0xff) << "." <<
                                        (host->h_addr_list[0][1] & 0xff) << "." <<
                                        (host->h_addr_list[0][2] & 0xff) << "." <<
                                        (host->h_addr_list[0][3] & 0xff) << ", port " <<
                                        static_cast<int>(peerPort) << std::endl;
 
    // Write resolved IP address of a server to the address structure
    memmove(&(server.sin_addr.s_addr), host->h_addr_list[0], 4);
 
    // Connect to the remote server
    int res = connect(s0, (struct sockaddr*) &server, sizeof(server));
    if (res < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }
 
    std::cout << "Connected writing a message to server" << std::endl;

	
	const std::string message = "<TestSuite><Test>Test1</Test></TestSuite>";
	
    write(s0, message.c_str(), message.length());
	
	char buffer[1024];
	
	//This read command will hold until something is written to the socket
    res = read(s0, buffer, 1023);
    if (res < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }
	
	buffer[1023] = '\0';
 
    std::cout << "Received:" << "\n" << buffer;
 
    close(s0);
    return 0;
}
 