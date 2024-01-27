// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABItemData.h"
#include "ABWeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class WITHMYALLY_API UABWeaponItemData : public UABItemData
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere,Category = ShortWeapon)
	//TObjectPtr<USkeletalMesh> WeaponMesh;
	TObjectPtr<UStaticMesh>WeaponMesh;

};
