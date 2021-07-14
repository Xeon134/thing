#pragma once

// Name: SoT, Version: 1.0.0

/*!!DEFINE!!*/

/*!!HELPER_DEF!!*/

/*!!HELPER_INC!!*/

#ifdef _MSC_VER
#pragma pack(push, 0x01)
#endif

#include "Engine_classes.h"

namespace CG
{
	// Class Athena.AthenaGameViewportClient
	// 0x0008 (FullSize[0x0258] - InheritedSize[0x0250])
	class UAthenaGameViewportClient : public UGameViewportClient
	{
	public:
		unsigned char UnknownData_PYKZ[0x8]; // 0x0250(0x0008) MISSED OFFSET (PADDING)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass(_xor_("Class Athena.AthenaGameViewportClient"));
			return ptr;
		}
	};
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif