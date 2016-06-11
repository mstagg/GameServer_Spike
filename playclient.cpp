#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
 
#define PORT 8010
#define NONBLOCKING 1


int main()
{
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

	// Set incoming apckets to nonblocking
	int nonblockingStatus = fcntl(socketID, F_SETFL, O_NONBLOCK, NONBLOCKING);
	if(nonblockingStatus < 0)
	{
		std::cout << "Failed to set packets to nonblocking." << std::endl;
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

    return 0;
}