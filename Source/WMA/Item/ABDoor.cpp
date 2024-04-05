// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AABDoor::AABDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Doorhand1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorhand1"));
	Doorhand2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorhand2"));
	DoorM1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorM1"));
	DoorM2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorM2"));
	DoorM3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorM3"));
	Doorname = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorname"));


	RootComponent = Door;
	Doorhand1->SetupAttachment(Door);
	Doorhand2->SetupAttachment(Doorhand1);

	DoorM1->SetupAttachment(Door);
	DoorM2->SetupAttachment(Door);
	DoorM3->SetupAttachment(Door);
	Doorname->SetupAttachment(Door);



	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Plane001.Doorfbx_Plane001'"));
	if (DoorMeshRef.Object) {
		Door->SetStaticMesh(DoorMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Doorhand1MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Box001.Doorfbx_Box001'"));
	if (Doorhand1MeshRef.Object) {
		Doorhand1->SetStaticMesh(Doorhand1MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Doorhand2MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Box002.Doorfbx_Box002'"));
	if (Doorhand2MeshRef.Object) {
		Doorhand2->SetStaticMesh(Doorhand2MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorM1MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Cylinder001.Doorfbx_Cylinder001'"));
	if (DoorM1MeshRef.Object) {
		DoorM1->SetStaticMesh(DoorM1MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorM2MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Cylinder002.Doorfbx_Cylinder002'"));
	if (DoorM2MeshRef.Object) {
		DoorM2->SetStaticMesh(DoorM2MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorM3MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Cylinder003.Doorfbx_Cylinder003'"));
	if (DoorM3MeshRef.Object) {
		DoorM3->SetStaticMesh(DoorM3MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoornameMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Plane002.Doorfbx_Plane002'"));
	if (DoornameMeshRef.Object) {
		Doorname->SetStaticMesh(DoornameMeshRef.Object);
	}


}


