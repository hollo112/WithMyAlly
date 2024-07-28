// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_BossJump.h"
#include "Interface/WMAAnimationJumpCheckInterface.h"

void UAnimNotify_BossJump::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IWMAAnimationJumpCheckInterface* AttackPawn = Cast<IWMAAnimationJumpCheckInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			UE_LOG(LogTemp, Log, TEXT("Boss Jump2"));
			AttackPawn->BossJumpCheck();
		}
	}
}
