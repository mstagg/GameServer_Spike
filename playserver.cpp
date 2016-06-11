#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
 
#define PORT 8008
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

	close(socketID);
    return 0;
}