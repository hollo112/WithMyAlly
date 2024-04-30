// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WMAWidgetAttacked2.h"
#include "Components/Image.h"

UWMAWidgetAttacked2::UWMAWidgetAttacked2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UWMAWidgetAttacked2::NativeConstruct()
{
	Super::NativeConstruct();

	SecondAttackedWidget = Cast<UImage>(GetWidgetFromName(TEXT("SecondAttackedIMG2")));
	ensure(SecondAttackedWidget);
}

void UWMAWidgetAttacked2::FadeInAnim()
{
	PlayAnimation(FadeIn);
}

void UWMAWidgetAttacked2::FadeOutAnim()
{
	PlayAnimation(FadeOut);
}
