// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ABItemData.h"
#include "ABWeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UABWeaponItemData : public UABItemData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = ShortWeapon)
	//TObjectPtr<USkeletalMesh> WeaponMesh;
		TObjectPtr<UStaticMesh>ShortWeaponMesh;

	UPROPERTY(EditAnywhere, Category = DisposableWeapon)
	TObjectPtr<UStaticMesh>DisposableWeaponMesh;

	UPROPERTY(EditAnywhere, Category = LongWeapon)
	TObjectPtr<UStaticMesh> LongWeaponMesh;

	UPROPERTY(EditAnywhere,Category = ThrowItem)
	TObjectPtr<UStaticMesh> ThrowItemMesh;

	UPROPERTY(EditAnywhere,Category = Gun)
	TObjectPtr<UStaticMesh> GunMesh;
};
