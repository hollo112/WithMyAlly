// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_Steps.h"
#include "Interface/WMAStepInterface.h"

void UAnimNotify_Steps::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IWMAStepInterface* AttackPawn = Cast<IWMAStepInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->StepCheck();
		}
	}
}
