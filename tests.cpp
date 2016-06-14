#include "src/Address.h"

#include <iostream>
#include <exception>

#include <stdlib.h>

#define NUM_TEST_CYCLES 125
#define MAX_PORT_SIZE 65535
#define MAX_IPV4_SIZE 4294967295

// Logs tests to determine if Address class is operating correctly
// Returns true if no errors occur
bool AddressTests()
{
    Address *address;
    uint8_t aOut, bOut, cOut, dOut;
    uint16_t portOut;
    uint32_t ipOut;
    bool success = true;
    
    // Test 1
    // 8008
    // 102.92.245.163 (1717368227)
    address = new Address(8008, 1717368227);
    address->GetIp(&aOut, &bOut, &cOut, &dOut);
    if(aOut != 102 || bOut != 92 || cOut != 245 || dOut != 163)
    {
        success = false;
        // LOG FAILURE
    }
    else
    {
        // LOG SUCCESS
    }
    
    // Test 2
    // 8396
    // 140.43.111.7 (2351656711)
    address = new Address(8008, 140, 43, 111, 7);
    ipOut = address->GetIp();
    if(ipOut != 2351656711u)
    {
        success = false;
        // LOG FAILURE
    }
    else
    {
        // LOG SUCCESS
    }
    
    // Test 3
    // 6001
    // 172.3.43.111 (2885888871)
    address = new Address(6001, 2885888871u);
    portOut = address->GetPort();
    if(portOut != 6001)
    {
        success = false;
        // LOG FAILURE
    }
    else
    {
        // LOG SUCCESS
    }
    
    /* USE FOR REFERENCE, DELETE AFTER USE
    try
    {
        address = new Address((int)-600, 2885888871u);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    */
	delete address;
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