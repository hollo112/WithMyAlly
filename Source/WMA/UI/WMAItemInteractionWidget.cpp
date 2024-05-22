// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/WMAItemInteractionWidget.h"
#include "Components/TextBlock.h"

UWMAItemInteractionWidget::UWMAItemInteractionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWMAItemInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemInteractionWidget = Cast<UTextBlock>(GetWidgetFromName(TEXT("InputE")));
	ensure(ItemInteractionWidget);
}
