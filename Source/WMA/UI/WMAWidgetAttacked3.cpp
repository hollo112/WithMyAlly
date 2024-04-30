// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WMAWidgetAttacked3.h"
#include "Components/Image.h"

UWMAWidgetAttacked3::UWMAWidgetAttacked3(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UWMAWidgetAttacked3::NativeConstruct()
{
	Super::NativeConstruct();

	ThirdAttackedWidget = Cast<UImage>(GetWidgetFromName(TEXT("ThirdAttackedIMG3")));
	ensure(ThirdAttackedWidget);
}

void UWMAWidgetAttacked3::FadeInAnim()
{
	PlayAnimation(FadeIn);
}

void UWMAWidgetAttacked3::FadeOutAnim()
{
	PlayAnimation(FadeOut);
}
