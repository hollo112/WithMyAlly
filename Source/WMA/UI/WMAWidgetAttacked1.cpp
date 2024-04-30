// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WMAWidgetAttacked1.h"
#include "Components/Image.h"

UWMAWidgetAttacked1::UWMAWidgetAttacked1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UWMAWidgetAttacked1::NativeConstruct()
{
	Super::NativeConstruct();

	FirstAttackedWidget = Cast<UImage>(GetWidgetFromName(TEXT("FirstAttackedIMG1")));
	ensure(FirstAttackedWidget);
}

void UWMAWidgetAttacked1::FadeInAnim()
{
	PlayAnimation(FadeIn);
}

void UWMAWidgetAttacked1::FadeOutAnim()
{
	PlayAnimation(FadeOut);
}
