#pragma once

// Name: SoT, Version: 1.0.0

/*!!DEFINE!!*/

/*!!HELPER_DEF!!*/

/*!!HELPER_INC!!*/

#ifdef _MSC_VER
#pragma pack(push, 0x01)
#endif

#include "InputCore_structs.h"

namespace CG
{
	//---------------------------------------------------------------------------
	// Classes
	//---------------------------------------------------------------------------

	// Class InputCore.InputCoreTypes
	// 0x0000 (FullSize[0x0028] - InheritedSize[0x0028])
	class UInputCoreTypes : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass(_xor_("Class InputCore.InputCoreTypes"));
			return ptr;
		}
	};
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
