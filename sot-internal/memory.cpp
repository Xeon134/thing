#include "memory.h"

Memory::Memory(MODULEINFO* gBaseMod) {
	this->gBaseMod = gBaseMod;
}

PBYTE Memory::FindPattern(const char* pattern) {
	const unsigned char* pat = reinterpret_cast<const unsigned char*>(pattern);
	PBYTE firstMatch = 0;
	auto base = static_cast<BYTE*>(gBaseMod->lpBaseOfDll);
	for (PBYTE pCur = base; pCur < base + gBaseMod->SizeOfImage - 1; ++pCur) {
		if (*(PBYTE)pat == (BYTE)'\?' || *pCur == getByte(pat)) {
			if (!firstMatch) {
				firstMatch = pCur;
			}
			pat += (*(PWORD)pat == (WORD)'\?\?' || *(PBYTE)pat != (BYTE)'\?') ? 3 : 2;
			if (!*pat) {
				return firstMatch;
			}
		}
		else if (firstMatch) {
			pCur = firstMatch;
			pat = reinterpret_cast<const unsigned char*>(pattern);
			firstMatch = 0;
		}
	}
	return NULL;
}