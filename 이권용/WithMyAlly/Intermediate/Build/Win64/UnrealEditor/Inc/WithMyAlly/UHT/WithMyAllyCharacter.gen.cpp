// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WithMyAlly/WithMyAllyCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWithMyAllyCharacter() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	UPackage* Z_Construct_UPackage__Script_WithMyAlly();
	WITHMYALLY_API UClass* Z_Construct_UClass_AWithMyAllyCharacter();
	WITHMYALLY_API UClass* Z_Construct_UClass_AWithMyAllyCharacter_NoRegister();
	WITHMYALLY_API UClass* Z_Construct_UClass_UABCharacterItemInterface_NoRegister();
	WITHMYALLY_API UScriptStruct* Z_Construct_UScriptStruct_FTakeItemDelegateWrapper();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_TakeItemDelegateWrapper;
class UScriptStruct* FTakeItemDelegateWrapper::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TakeItemDelegateWrapper.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_TakeItemDelegateWrapper.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTakeItemDelegateWrapper, (UObject*)Z_Construct_UPackage__Script_WithMyAlly(), TEXT("TakeItemDelegateWrapper"));
	}
	return Z_Registration_Info_UScriptStruct_TakeItemDelegateWrapper.OuterSingleton;
}
template<> WITHMYALLY_API UScriptStruct* StaticStruct<FTakeItemDelegateWrapper>()
{
	return FTakeItemDelegateWrapper::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FTakeItemDelegateWrapper_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTakeItemDelegateWrapper_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FTakeItemDelegateWrapper_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTakeItemDelegateWrapper>();
	}
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTakeItemDelegateWrapper_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_WithMyAlly,
		nullptr,
		&NewStructOps,
		"TakeItemDelegateWrapper",
		nullptr,
		0,
		sizeof(FTakeItemDelegateWrapper),
		alignof(FTakeItemDelegateWrapper),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTakeItemDelegateWrapper_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTakeItemDelegateWrapper_Statics::Struct_MetaDataParams)
	};
	UScriptStruct* Z_Construct_UScriptStruct_FTakeItemDelegateWrapper()
	{
		if (!Z_Registration_Info_UScriptStruct_TakeItemDelegateWrapper.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_TakeItemDelegateWrapper.InnerSingleton, Z_Construct_UScriptStruct_FTakeItemDelegateWrapper_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_TakeItemDelegateWrapper.InnerSingleton;
	}
	void AWithMyAllyCharacter::StaticRegisterNativesAWithMyAllyCharacter()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWithMyAllyCharacter);
	UClass* Z_Construct_UClass_AWithMyAllyCharacter_NoRegister()
	{
		return AWithMyAllyCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AWithMyAllyCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Weapon_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Weapon;
		static const UECodeGen_Private::FStructPropertyParams NewProp_TakeItemActions_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TakeItemActions_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_TakeItemActions;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AWithMyAllyCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_WithMyAlly,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "WithMyAllyCharacter.h" },
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWithMyAllyCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_CameraBoom_MetaData), Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_CameraBoom_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Follow camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Follow camera" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWithMyAllyCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_FollowCamera_MetaData), Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_FollowCamera_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** MappingContext */" },
#endif
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "MappingContext" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWithMyAllyCharacter, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_DefaultMappingContext_MetaData), Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_DefaultMappingContext_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_JumpAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWithMyAllyCharacter, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_JumpAction_MetaData), Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_JumpAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_MoveAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWithMyAllyCharacter, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_MoveAction_MetaData), Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_MoveAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_LookAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWithMyAllyCharacter, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_LookAction_MetaData), Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_LookAction_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_Weapon_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Equipment" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_Weapon = { "Weapon", nullptr, (EPropertyFlags)0x00240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWithMyAllyCharacter, Weapon), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_Weapon_MetaData), Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_Weapon_MetaData) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_TakeItemActions_Inner = { "TakeItemActions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTakeItemDelegateWrapper, METADATA_PARAMS(0, nullptr) }; // 2764138843
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_TakeItemActions_MetaData[] = {
		{ "ModuleRelativePath", "WithMyAllyCharacter.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_TakeItemActions = { "TakeItemActions", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWithMyAllyCharacter, TakeItemActions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_TakeItemActions_MetaData), Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_TakeItemActions_MetaData) }; // 2764138843
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWithMyAllyCharacter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_CameraBoom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_FollowCamera,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_DefaultMappingContext,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_JumpAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_MoveAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_LookAction,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_Weapon,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_TakeItemActions_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWithMyAllyCharacter_Statics::NewProp_TakeItemActions,
	};
		const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UABCharacterItemInterface_NoRegister, (int32)VTABLE_OFFSET(AWithMyAllyCharacter, IABCharacterItemInterface), false },  // 4197360937
		};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::InterfaceParams) < 64);
	const FCppClassTypeInfoStatic Z_Construct_UClass_AWithMyAllyCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWithMyAllyCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AWithMyAllyCharacter_Statics::ClassParams = {
		&AWithMyAllyCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AWithMyAllyCharacter_Statics::PropPointers,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::PropPointers),
		UE_ARRAY_COUNT(InterfaceParams),
		0x008000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AWithMyAllyCharacter_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWithMyAllyCharacter_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AWithMyAllyCharacter()
	{
		if (!Z_Registration_Info_UClass_AWithMyAllyCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWithMyAllyCharacter.OuterSingleton, Z_Construct_UClass_AWithMyAllyCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AWithMyAllyCharacter.OuterSingleton;
	}
	template<> WITHMYALLY_API UClass* StaticClass<AWithMyAllyCharacter>()
	{
		return AWithMyAllyCharacter::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AWithMyAllyCharacter);
	AWithMyAllyCharacter::~AWithMyAllyCharacter() {}
	struct Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyCharacter_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyCharacter_h_Statics::ScriptStructInfo[] = {
		{ FTakeItemDelegateWrapper::StaticStruct, Z_Construct_UScriptStruct_FTakeItemDelegateWrapper_Statics::NewStructOps, TEXT("TakeItemDelegateWrapper"), &Z_Registration_Info_UScriptStruct_TakeItemDelegateWrapper, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTakeItemDelegateWrapper), 2764138843U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AWithMyAllyCharacter, AWithMyAllyCharacter::StaticClass, TEXT("AWithMyAllyCharacter"), &Z_Registration_Info_UClass_AWithMyAllyCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWithMyAllyCharacter), 936022189U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyCharacter_h_1434930252(TEXT("/Script/WithMyAlly"),
		Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyCharacter_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyCharacter_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_WithMyAllyCharacter_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
