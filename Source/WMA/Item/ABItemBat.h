// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/ABCharacterItemInterface.h"
#include "GameFramework/Actor.h"
#include "ABItemBat.generated.h"

UCLASS()
class WMA_API AABItemBat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemBat();

	virtual void Tick(float DeltaTime) override;
	
protected:

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	TObjectPtr<class UParticleSystemComponent> Effect;

	UPROPERTY(EditAnywhere, Category = Item)
	TObjectPtr<class UABItemData>Item;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* ParticleSystem);

	TObjectPtr<class UBoxComponent> TempTrigger;
	TObjectPtr<class UStaticMeshComponent> TempMesh;
	TObjectPtr<class UParticleSystemComponent> TempEffect;

	UStaticMesh* TempBoxMesh;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> TextE;

	TSubclassOf<UUserWidget> InteractionItemWidgetClass;

	UUserWidget* ItemText;

	UPROPERTY()
	TObjectPtr<class AActor> MyPlayer;
public:

	void StartInteractionItem();
	void StopInteractionItem();

	UPROPERTY()
	uint8 bInteractionItem : 1;
};
