// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perception/AISense_Hearing.h"
#include "ABItemSiren.generated.h"

UCLASS()
class WMA_API AABItemSiren : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemSiren();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Replicated, Category = Box)
    TObjectPtr<class UBoxComponent> CollisionBox;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Mesh")
    class UStaticMeshComponent* Siren;

    UPROPERTY(EditAnywhere, Replicated, Category = Item)
    TObjectPtr<class UABItemData>Item;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UStaticMesh* TempBoxMesh;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UWidgetComponent> TextE;

    TSubclassOf<UUserWidget> InteractionButtonWidgetClass;

    UUserWidget* ItemWidget;

    AActor* PlayerActor;

    bool bIsHolding = false;

    void MakeSound();

public:
    void OnInteract();

    UAISense_Hearing* AISenseHearing;
protected:
    UFUNCTION(Client, Reliable)
    void ServerRPCInteract();
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCInteract();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    void ATDTSiren();
};
