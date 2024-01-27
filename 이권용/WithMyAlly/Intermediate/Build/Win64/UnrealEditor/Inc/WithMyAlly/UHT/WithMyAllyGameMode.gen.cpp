// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WithMyAlly/WithMyAllyGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWithMyAllyGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_WithMyAlly();
	WITHMYALLY_API UClass* Z_Construct_UClass_AWithMyAllyGameMode();
	WITHMYALLY_API UClass* Z_Construct_UClass_AWithMyAllyGameMode_NoRegister();
// End Cross Module References
	void AWithMyAllyGameMode::StaticRegisterNativesAWithMyAllyGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWithMyAllyGameMode);
	UClass* Z_Construct_UClass_AWithMyAllyGameMode_NoRegister()
	{
		return AWithMyAllyGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AWithMyAllyGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWithMyAllyGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_WithMyAlly,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "WithMyAllyGameMode.h" },
		{ "ModuleRelativePath", "WithMyAllyGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWithMyAllyGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWithMyAllyGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWithMyAllyGameMode_Statics::ClassParams = {
		&AWithMyAllyGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AWithMyAllyGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AWithMyAllyGameMode()
	{
		if (!Z_Registration_Info_UClass_AWithMyAllyGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWithMyAllyGameMode.OuterSingleton, Z_Construct_UClass_AWithMyAllyGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWithMyAllyGameMode.OuterSingleton;
	}
	template<> WITHMYALLY_API UClass* StaticClass<AWithMyAllyGameMode>()
	{
		return AWithMyAllyGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWithMyAllyGameMode);
	AWithMyAllyGameMode::~AWithMyAllyGameMode() {}
	struct Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWithMyAllyGameMode, AWithMyAllyGameMode::StaticClass, TEXT("AWithMyAllyGameMode"), &Z_Registration_Info_UClass_AWithMyAllyGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWithMyAllyGameMode), 3944919299U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyGameMode_h_3810069346(TEXT("/Script/WithMyAlly"),
		Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
