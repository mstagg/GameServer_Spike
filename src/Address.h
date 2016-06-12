#ifndef ADDRESS_H
#define ADDRESS_H

#include <stdint.h>

class Address
{
public:
	Address(uint16_t, uint8_t, uint8_t, uint8_t, uint8_t);
	Address(uint16_t, uint32_t);
	~Address();
	void GetIp(uint8_t*, uint8_t*, uint8_t*, uint8_t*);
	void SetPort(uint16_t);
	void SetIp(uint32_t);
	void SetIp(uint8_t, uint8_t, uint8_t, uint8_t);
	uint16_t GetPort();
	uint32_t GetIp();
private:
	// IP as four component parts: aaa.bbb.ccc.ddd 
	// Individual 8 bit IP components range from 0 - 255
	// 32 bit IP ranges from 0 - 4294967295
	uint8_t a, b, c, d;
	// Port number 0 - 65535
	uint16_t port;
};

#endif
