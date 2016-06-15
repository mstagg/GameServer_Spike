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
    return WSAStartup(MAKEWORD(2,2), &WsaData);
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

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl((127 << 24) | (0 << 16) | (0 << 8) | 1);
	address.sin_port = htons( (unsigned short) 8008 );

	char packet_data[20] = "Hello, World!";
	int packet_size = 14;
	int sent_bytes = sendto( socketID, (const char*)packet_data, packet_size, 0, (sockaddr*)&address, sizeof(sockaddr_in) );
	if ( sent_bytes != packet_size )
	{
	    std::cout << "failed to send packet\n" << std::endl;;
	    return -1;
	}
    
    #if OPERATING_SYS == WINDOWS
	closesocket(socketID);
    #else
    close(socketID);
    #endif
    
    ShutdownSockets();
    return 0;
}