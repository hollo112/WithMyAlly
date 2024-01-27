// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WithMyAlly/Item/ABItemFruitSwd.h"
#include "../../Source/Runtime/Engine/Classes/Engine/HitResult.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeABItemFruitSwd() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UParticleSystemComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	UPackage* Z_Construct_UPackage__Script_WithMyAlly();
	WITHMYALLY_API UClass* Z_Construct_UClass_AABItemFruitSwd();
	WITHMYALLY_API UClass* Z_Construct_UClass_AABItemFruitSwd_NoRegister();
	WITHMYALLY_API UClass* Z_Construct_UClass_UABItemData_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AABItemFruitSwd::execOnEffectFinished)
	{
		P_GET_OBJECT(UParticleSystemComponent,Z_Param_ParticleSystem);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnEffectFinished(Z_Param_ParticleSystem);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AABItemFruitSwd::execOnOverlapBegin)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent);
		P_GET_OBJECT(AActor,Z_Param_OtherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
		P_GET_UBOOL(Z_Param_bFromSweep);
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepHitResult);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnOverlapBegin(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepHitResult);
		P_NATIVE_END;
	}
	void AABItemFruitSwd::StaticRegisterNativesAABItemFruitSwd()
	{
		UClass* Class = AABItemFruitSwd::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnEffectFinished", &AABItemFruitSwd::execOnEffectFinished },
			{ "OnOverlapBegin", &AABItemFruitSwd::execOnOverlapBegin },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics
	{
		struct ABItemFruitSwd_eventOnEffectFinished_Parms
		{
			UParticleSystemComponent* ParticleSystem;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ParticleSystem_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ParticleSystem;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::NewProp_ParticleSystem_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::NewProp_ParticleSystem = { "ParticleSystem", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABItemFruitSwd_eventOnEffectFinished_Parms, ParticleSystem), Z_Construct_UClass_UParticleSystemComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::NewProp_ParticleSystem_MetaData), Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::NewProp_ParticleSystem_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::NewProp_ParticleSystem,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Item/ABItemFruitSwd.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AABItemFruitSwd, nullptr, "OnEffectFinished", nullptr, nullptr, Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::PropPointers), sizeof(Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::ABItemFruitSwd_eventOnEffectFinished_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::Function_MetaDataParams), Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::ABItemFruitSwd_eventOnEffectFinished_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics
	{
		struct ABItemFruitSwd_eventOnOverlapBegin_Parms
		{
			UPrimitiveComponent* OverlappedComponent;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComp;
			int32 OtherBodyIndex;
			bool bFromSweep;
			FHitResult SweepHitResult;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedComponent;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
		static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
		static void NewProp_bFromSweep_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SweepHitResult_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_SweepHitResult;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OverlappedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OverlappedComponent = { "OverlappedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABItemFruitSwd_eventOnOverlapBegin_Parms, OverlappedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OverlappedComponent_MetaData), Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OverlappedComponent_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABItemFruitSwd_eventOnOverlapBegin_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABItemFruitSwd_eventOnOverlapBegin_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OtherComp_MetaData), Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OtherComp_MetaData) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABItemFruitSwd_eventOnOverlapBegin_Parms, OtherBodyIndex), METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_bFromSweep_SetBit(void* Obj)
	{
		((ABItemFruitSwd_eventOnOverlapBegin_Parms*)Obj)->bFromSweep = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABItemFruitSwd_eventOnOverlapBegin_Parms), &Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_SweepHitResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_SweepHitResult = { "SweepHitResult", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABItemFruitSwd_eventOnOverlapBegin_Parms, SweepHitResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_SweepHitResult_MetaData), Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_SweepHitResult_MetaData) }; // 1891709922
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OverlappedComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OtherActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OtherComp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_OtherBodyIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_bFromSweep,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::NewProp_SweepHitResult,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Item/ABItemFruitSwd.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AABItemFruitSwd, nullptr, "OnOverlapBegin", nullptr, nullptr, Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::PropPointers), sizeof(Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::ABItemFruitSwd_eventOnOverlapBegin_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::Function_MetaDataParams), Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::ABItemFruitSwd_eventOnOverlapBegin_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AABItemFruitSwd);
	UClass* Z_Construct_UClass_AABItemFruitSwd_NoRegister()
	{
		return AABItemFruitSwd::StaticClass();
	}
	struct Z_Construct_UClass_AABItemFruitSwd_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Trigger_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Trigger;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Mesh;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Effect_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Effect;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Item_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Item;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AABItemFruitSwd_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_WithMyAlly,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AABItemFruitSwd_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_AABItemFruitSwd_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AABItemFruitSwd_OnEffectFinished, "OnEffectFinished" }, // 1693363149
		{ &Z_Construct_UFunction_AABItemFruitSwd_OnOverlapBegin, "OnOverlapBegin" }, // 931040109
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AABItemFruitSwd_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AABItemFruitSwd_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Item/ABItemFruitSwd.h" },
		{ "ModuleRelativePath", "Item/ABItemFruitSwd.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Trigger_MetaData[] = {
		{ "Category", "Box" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Item/ABItemFruitSwd.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Trigger = { "Trigger", nullptr, (EPropertyFlags)0x00240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AABItemFruitSwd, Trigger), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Trigger_MetaData), Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Trigger_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Mesh_MetaData[] = {
		{ "Category", "Box" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Item/ABItemFruitSwd.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AABItemFruitSwd, Mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Mesh_MetaData), Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Mesh_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Effect_MetaData[] = {
		{ "Category", "Effect" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Item/ABItemFruitSwd.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Effect = { "Effect", nullptr, (EPropertyFlags)0x00240800000a0009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AABItemFruitSwd, Effect), Z_Construct_UClass_UParticleSystemComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Effect_MetaData), Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Effect_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Item_MetaData[] = {
		{ "Category", "Item" },
		{ "ModuleRelativePath", "Item/ABItemFruitSwd.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Item = { "Item", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AABItemFruitSwd, Item), Z_Construct_UClass_UABItemData_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Item_MetaData), Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Item_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AABItemFruitSwd_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Trigger,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Mesh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Effect,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AABItemFruitSwd_Statics::NewProp_Item,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AABItemFruitSwd_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AABItemFruitSwd>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AABItemFruitSwd_Statics::ClassParams = {
		&AABItemFruitSwd::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AABItemFruitSwd_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AABItemFruitSwd_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AABItemFruitSwd_Statics::Class_MetaDataParams), Z_Construct_UClass_AABItemFruitSwd_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AABItemFruitSwd_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AABItemFruitSwd()
	{
		if (!Z_Registration_Info_UClass_AABItemFruitSwd.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AABItemFruitSwd.OuterSingleton, Z_Construct_UClass_AABItemFruitSwd_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AABItemFruitSwd.OuterSingleton;
	}
	template<> WITHMYALLY_API UClass* StaticClass<AABItemFruitSwd>()
	{
		return AABItemFruitSwd::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AABItemFruitSwd);
	AABItemFruitSwd::~AABItemFruitSwd() {}
	struct Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_Item_ABItemFruitSwd_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_Item_ABItemFruitSwd_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AABItemFruitSwd, AABItemFruitSwd::StaticClass, TEXT("AABItemFruitSwd"), &Z_Registration_Info_UClass_AABItemFruitSwd, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AABItemFruitSwd), 2371832210U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_Item_ABItemFruitSwd_h_3269098994(TEXT("/Script/WithMyAlly"),
		Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_Item_ABItemFruitSwd_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_WithMyAlly_Source_WithMyAlly_Item_ABItemFruitSwd_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
