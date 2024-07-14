// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ThrowCheck.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UAnimNotify_ThrowCheck : public UAnimNotify
{
	GENERATED_BODY()
	
	protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
