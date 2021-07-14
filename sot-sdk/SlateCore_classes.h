#pragma once

// Name: SoT, Version: 1.0.0

/*!!DEFINE!!*/

/*!!HELPER_DEF!!*/

/*!!HELPER_INC!!*/

#ifdef _MSC_VER
#pragma pack(push, 0x01)
#endif

#include "SlateCore_structs.h"

namespace CG
{
	//---------------------------------------------------------------------------
	// Classes
	//---------------------------------------------------------------------------

	// Class SlateCore.FontBulkData
	// 0x0098 (FullSize[0x00C0] - InheritedSize[0x0028])
	class UFontBulkData : public UObject
	{
	public:
		unsigned char                                      UnknownData_I31K[0x98];                                    // 0x0028(0x0098) MISSED OFFSET (PADDING)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass(_xor_("Class SlateCore.FontBulkData"));
			return ptr;
		}
	};

	// Class SlateCore.FontProviderInterface
	// 0x0000 (FullSize[0x0028] - InheritedSize[0x0028])
	class UFontProviderInterface : public UInterface
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass(_xor_("Class SlateCore.FontProviderInterface"));
			return ptr;
		}
	};

	// Class SlateCore.SlateTypes
	// 0x0000 (FullSize[0x0028] - InheritedSize[0x0028])
	class USlateTypes : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass(_xor_("Class SlateCore.SlateTypes"));
			return ptr;
		}
	};

	// Class SlateCore.SlateWidgetStyleContainerInterface
	// 0x0000 (FullSize[0x0028] - InheritedSize[0x0028])
	class USlateWidgetStyleContainerInterface : public UInterface
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass(_xor_("Class SlateCore.SlateWidgetStyleContainerInterface"));
			return ptr;
		}
	};

	// Class SlateCore.SlateWidgetStyleContainerBase
	// 0x0008 (FullSize[0x0030] - InheritedSize[0x0028])
	class USlateWidgetStyleContainerBase : public UObject
	{
	public:
		unsigned char                                      UnknownData_Y12S[0x8];                                     // 0x0028(0x0008) MISSED OFFSET (PADDING)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass(_xor_("Class SlateCore.SlateWidgetStyleContainerBase"));
			return ptr;
		}
	};

	// Class SlateCore.SlateWidgetStyleAsset
	// 0x0008 (FullSize[0x0030] - InheritedSize[0x0028])
	class USlateWidgetStyleAsset : public UObject
	{
	public:
		class USlateWidgetStyleContainerBase* CustomStyle;                                               // 0x0028(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, PersistentInstance, HasGetValueTypeHash)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass(_xor_("Class SlateCore.SlateWidgetStyleAsset"));
			return ptr;
		}
	};
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
