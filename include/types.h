#ifndef VM_TYPES_H
#define VM_TYPES_H

#include <cstdint>

using word = uint8_t;
using addr_t = uint16_t;

using code_t = uint8_t;

struct psw_t 
{
	addr_t ip;
	struct flags_t
	{
		uint8_t ip_changed : 1;
		uint8_t nf : 1;
		uint8_t zf : 1;
		word moc : 5;
	} flags;	
};

union converter
{
	word data[4];
	float floating;
	uint32_t wide_unsigned;
	uint16_t short_unsigned[2];
	int32_t wide_signed;
	int16_t short_signed[2];
	int8_t relation;
};

struct state 
{
	addr_t reg[7];
	addr_t bp;
	addr_t sp;
	psw_t psw;
};

struct command16 
{
 	code_t cop : 7;
	uint8_t a1 : 3;
	uint8_t a2 : 3;
	uint8_t a3 : 3;
};

struct command24 
{
	code_t cop : 7;
	uint8_t b : 1;
	word addr;
};

struct command32 
{
	code_t cop : 7;
	uint8_t a1 : 3;
	uint8_t a2 : 3;
	uint8_t a3 : 3;
	word addr;
};

union command
{
	code_t c8;
	command16 c16;
	command24 c24;
	command32 c32;
	word parts[4];
};

#endif