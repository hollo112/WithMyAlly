// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Perception/AISense_Hearing.h"
#include "WMAThrowingObject.generated.h"

UCLASS()
class WMA_API AWMAThrowingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWMAThrowingObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultScene;

	UPROPERTY(VisibleAnywhere, Replicated, Category = Sphere)
	TObjectPtr<class USphereComponent> CollisionSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Box)
    TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	bool isHit = false;

	// AI Hearing
public:
	UAISense_Hearing* AISenseHearing;
};
