// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WMAFireExtinguisher.generated.h"

UCLASS()
class WMA_API AWMAFireExtinguisher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWMAFireExtinguisher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UPROPERTY(VisibleAnywhere, Replicated, Category = Box)
    TObjectPtr<class UBoxComponent> CollisionBox;

    UPROPERTY(VisibleAnywhere, Replicated, Category = Capsule)
    TObjectPtr<class UCapsuleComponent> CollisionCapsule;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Mesh")
    class UStaticMeshComponent* FireExt;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Mesh")
    class UStaticMeshComponent* FireExtBody;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Mesh")
    class UStaticMeshComponent* FireExtSmoke;

    UPROPERTY(EditAnywhere, Replicated, Category = Item)
    TObjectPtr<class UABItemData>Item;

   UPROPERTY(BlueprintReadWrite, Replicated, Category = "FX")
    TObjectPtr<class UNiagaraSystem> SmokeSystem;

    UPROPERTY(BlueprintReadWrite, Replicated, Category = "FX")
    TObjectPtr<class UNiagaraComponent> NiagaraComp;


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

    bool bIsHoldOnce = false;
    bool bTurnOn = false;
public:
    void OnInteract();
    void TurnOnFireExt();

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Mesh")
    uint8 bIsHolding : 1;

protected:
    UFUNCTION(Client, Reliable)
    void ServerRPCInteract();
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCInteract();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    UPROPERTY(VisibleAnywhere, Replicated, Category = "Mesh")
    uint8 bIsVisible : 1;
   

    void ATDTFireExt();

    UFUNCTION(Client, Reliable)
    void ServerRPCOverlap(AActor* OtherActor);
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCOverlap(AActor* OtherActor);

    UFUNCTION(Client, Reliable)
    void ServerRPCOverlapEnd(AActor* OtherActor);
    UFUNCTION(NetMulticast, Reliable)
    void MulticastRPCOverlapEnd(AActor* OtherActor);

};
