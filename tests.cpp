#include "src/Address.h"

#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <math.h>

#define NUM_TEST_CYCLES 125
#define MAX_PORT_SIZE 65535
#define MAX_IPV4_SIZE 4294967295

// Logs tests to determine if Address class is operating correctly
// Returns true if no errors occur
bool AddressTests()
{
	uint8_t a, b, c, d, aOut, bOut, cOut, dOut;
	uint16_t port;
	uint32_t ip32;
	bool success = true;
	std::ofstream logFile;
	Address *addr;

	logFile.open("logs/AddressTestLog.txt", std::ios::trunc);

	for(int i = 0; i < NUM_TEST_CYCLES; i++)
	{
		port = rand() % (MAX_PORT_SIZE + 1);
		ip32 = rand() % (MAX_IPV4_SIZE + 1);
		a = (ip32 & 0xff000000) >> 24;
		b = (ip32 & 0x00ff0000) >> 16;
		c = (ip32 & 0x0000ff00) >> 8;
		d = (ip32 & 0x000000ff);

		addr = new Address(port, ip32);
		addr->GetIp(&aOut, &bOut, &cOut, &dOut);

		logFile << "-- ADDRESS TEST " << i + 1 << "--" << std::endl; 
		logFile << "Standard IP: " << (int)a << "." << (int)b << "." << (int)c << "." << (int)d << std::endl;
		logFile << "32 bit IP: " << (int)ip32 << std::endl;
		logFile << "Port: " << (int)addr->GetPort() << std::endl;

		if(addr->GetPort() != port)
		{
			logFile << "ERROR: PORTS DID NOT MATCH!" << std::endl << std::endl;
			success = false;
		}
		else if(addr->GetIp() != ip32)
		{
			logFile << "ERROR: 32 BIT IP VALUE DID NOT MATCH!" << std::endl << std::endl;
			success = false;
		}
		else if(aOut != a || bOut != b || cOut != c || dOut != d)
		{
			logFile << "ERROR: INDIVIDUAL 8 BIT IP VALUES DID NOT MATCH!" << std::endl << std::endl;
			success = false;
		}
		else if(addr->GetPort() > 65535 || addr->GetPort() < 0)
		{
			logFile << "ERROR: PORT VALUE IS OUT OF RANGE (0 - 65535)!" << std::endl << std::endl;
			success = false;
		}
		else if(addr->GetIp() > 4294967295 || addr->GetIp() < 0)
		{
			logFile << "ERROR: 32 BIT IP VALUE IS OUT OF RANGE (0 - 4294967295)!" << std::endl << std::endl;
			success = false;
		}
		else if((aOut > 255 || aOut < 0) || (bOut > 255 || bOut < 0) || (cOut > 255 || cOut < 0) || (dOut > 255 || dOut < 0))
		{
			logFile << "ERROR: INDIVIDUAL 8 BIT IP VALUE IS OUT OF RANGE (0 - 255)!" << std::endl << std::endl;
			success = false;
		}
		else
		{
			logFile << "NO ERRORS FOR TEST " << i + 1 << std::endl << std::endl;
		}
	}

	delete addr;
	logFile.close();
	return success;
}

int main()
{
	if(AddressTests())
	{
		std::cout << "Address Tests Succesful!" << std::endl;
	}
	else
	{
		std::cout << "Address Tests Failed, See logs!" << std::endl;
	}

	return 0;
}