#pragma once
#include <windows.h>
#include <Psapi.h>
#include "logger.h"

#define INRANGE(x,a,b) (x >= a && x <= b)
#define getBits( x ) (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x ) (getBits(x[0]) << 4 | getBits(x[1]))

class Memory {
public:
	Memory(MODULEINFO*);

	template <typename T>
	inline T Read(uintptr_t address) {
		return *(T*)gBaseMod->lpBaseOfDll + address;
	}

	PBYTE FindPattern(const char*);

private:
	static inline MODULEINFO* gBaseMod;
};