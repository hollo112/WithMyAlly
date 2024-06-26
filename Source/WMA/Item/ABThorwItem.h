// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WMACharacterPlayer.h"
#include "Interface/ABCharacterItemInterface.h"
#include "GameFramework/Actor.h"
#include "ABThorwItem.generated.h"


UCLASS()
class WMA_API AABThorwItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABThorwItem();

protected:
    virtual void BeginPlay() override;

protected:

    UPROPERTY(VisibleAnywhere, Category = Box)
    TObjectPtr<class UBoxComponent> Trigger;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Box)
    TObjectPtr<class UStaticMeshComponent> Mesh;

    UPROPERTY(VisibleAnywhere, Category = Effect)
    TObjectPtr<class UParticleSystemComponent> Effect;

    UPROPERTY(EditAnywhere, Category = Item)
    TObjectPtr<class UABItemData>Item;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundBase* ImpactSound;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void OnEffectFinished(class UParticleSystemComponent* ParticleSystem); 
    
    UStaticMesh* TempBoxMesh;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UWidgetComponent> TextE;

    TSubclassOf<UUserWidget> InteractionItemWidgetClass;

    UUserWidget* ItemWidget;

    AActor* PlayerActor;
public:
    void OnInteract();

};
