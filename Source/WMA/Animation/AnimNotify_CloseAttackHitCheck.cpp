// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_CloseAttackHitCheck.h"
#include "Interface/WMAAnimationCloseAttackInterface.h"

void UAnimNotify_CloseAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IWMAAnimationCloseAttackInterface* AttackPawn = Cast<IWMAAnimationCloseAttackInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->CloseAttackHitCheck();
		}
	}
}
