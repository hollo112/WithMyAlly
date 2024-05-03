// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WMAItemInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UWMAItemInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UWMAItemInteractionWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

protected:

	UPROPERTY()
	TObjectPtr<class UTextBlock> ItemInteractionWidget;

};
