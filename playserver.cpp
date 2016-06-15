#include <iostream>
#include <stdlib.h>
#include <unistd.h>
 
#define PORT 8008
#define NONBLOCKING 1

#define WINDOWS 0
#define MAC 1
#define UNIX 2

#if defined(_WIN32)
    #define OPERATING_SYS WINDOWS
#elif defined(__APPLE__)
    #define OPERATING_SYS MAC
#else
    #define OPERATING_SYS UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS
    #include <winsock2.h>
    #pragma comment( lib, "wsock32.lib" )
    typedef int32_t socklen_t;
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <fcntl.h>
#endif

int InitSockets()
{
    #if OPERATING_SYS == WINDOWS
    WSADATA WsaData;
    return WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR;
    #else
    return 0;
    #endif
}

void ShutdownSockets()
{
    #if OPERATING_SYS == WINDOWS
    WSACleanup();
    #endif
}

int main()
{
    if(InitSockets() < 0)
    {
		std::cout << "Failed to intialize socket interface." << std::endl;
		return -1; 
    }
    
	// Create socket and check for failure
	int socketID = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(socketID < 0)
	{
		std::cout << "Failed to intialize socket." << std::endl;
		return -1;
	} 

	// Create socket address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons((unsigned short) PORT);

	// Bind address to socket and check for failure
	int bondedSocket = bind(socketID, (const sockaddr*) &address, sizeof(sockaddr_in));
	if(bondedSocket < 0)
	{
		std::cout << "Failed to bind address to socket." << std::endl;
		return -1;
	}

	// Set incoming packets to nonblocking
    #if OPERATING_SYS == WINDOWS
    DWORD nonBlocking = 1;
    int nonblockingStatus = ioctlsocket(socketID, FIONBIO, &nonBlocking);
    #else
	int nonblockingStatus = fcntl(socketID, F_SETFL, O_NONBLOCK, NONBLOCKING);
    #endif
	if(nonblockingStatus < 0)
	{
		std::cout << "Failed to set packets to nonblocking." << std::endl;
		return -1;
	}
    
	while ( true )
	{
	    unsigned char packet_data[256];

	    unsigned int max_packet_size = sizeof(packet_data);

	    sockaddr_in from;
	    socklen_t fromLength = sizeof(from);

	    int bytes = recvfrom(socketID, (char*)packet_data, max_packet_size, 0, (sockaddr*)&from, &fromLength);  

	    unsigned int from_address = ntohl( from.sin_addr.s_addr );

	    unsigned int from_port = ntohs( from.sin_port );


		if (bytes > 0 )
		{
			std::cout << packet_data << std::endl;
		}
	    // process received packet
	}

    #if OPERATING_SYS == WINDOWS
	closesocket(socketID);
    #else
    close(socketID);
    #endif
    
    ShutdownSockets();
    return 0;
}