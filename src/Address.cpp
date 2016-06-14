#include "Address.h"

/* USE FOR REFERENCE, DELETE AFTER USE
#include <exception>
class myexception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "My exception happened";
  }
} myex;
*/
// Constructor using 4 component parts of IPv4 address
Address::Address(uint16_t portNumber, uint8_t ipA, uint8_t ipB, uint8_t ipC, uint8_t ipD)
{
	this->SetPort(portNumber);
	this->a = ipA;
	this->b = ipB;
	this->c = ipC;
	this->d = ipD;
}

// Constructor using single IPv4 address
Address::Address(uint16_t portNumber, uint32_t ip)
{
    /* USE FOR REFERENCE, DELETE AFTER USE
    if(portNumber < 0)
    {
        throw myex;
    }
    */
	this->SetPort(portNumber);
	this->SetIp(ip);
}

// Destructor
Address::~Address()
{

}

// Returns IP address as 4 component parts
void Address::GetIp(uint8_t *aOut, uint8_t *bOut, uint8_t *cOut, uint8_t *dOut)
{
	*aOut = this->a;
	*bOut = this->b;
	*cOut = this->c;
	*dOut = this->d;
}

// Setter for port
void Address::SetPort(uint16_t newPortNumber)
{
	this->port = newPortNumber;
}

// Setter for IP that takes single IPv4 address
void Address::SetIp(uint32_t newIpNumber)
{
	this->a = (newIpNumber & 0xff000000) >> 24;
	this->b = (newIpNumber & 0x00ff0000) >> 16;
	this->c = (newIpNumber & 0x0000ff00) >> 8;
	this->d = (newIpNumber & 0x000000ff);
}

// Setter for IP that takes 4 component parts instead of single value
void Address::SetIp(uint8_t newA, uint8_t newB, uint8_t newC, uint8_t newD)
{
	this->a = newA;
	this->b = newB;
	this->c = newC;
	this->d = newD;
}

// Returns port number
uint16_t Address::GetPort()
{
	return this->port;
}

// Returns IP address as a single IPv4 address
uint32_t Address::GetIp()
{
	uint32_t ip = (this->a << 24);
	ip += (this->b << 16);
	ip += (this->c << 8);
	ip += (this->d);
	return ip;
}