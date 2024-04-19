// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WMACharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Physics/WMACollsion.h"
#include "Engine/DamageEvents.h"
#include "CharacterStat/WMACharacterStatComponent.h"
#include "Item/ABWeaponItemData.h"
#include "GameData/WMAGameInstance.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
AWMACharacterBase::AWMACharacterBase()
{
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_WMACAPSULE);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Animation/Female/Female_walk_animation.Female_walk_animation'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Animation/Female/ABP_WMA_FemaleCharacter.ABP_WMA_FemaleCharacter_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Dead.AM_Dead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	// Stat Component
	Stat = CreateDefaultSubobject<UWMACharacterStatComponent>(TEXT("Stat"));

	// Item Actions
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AWMACharacterBase::EquipShort)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AWMACharacterBase::EquipDisposable)));
	TakeItemActions.Add(FTakeItemDelegateWrapper(FOnTakeItemDelegate::CreateUObject(this, &AWMACharacterBase::EquipLong)));

	// Weapon Component
	ShortWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShortWeapon"));
	ShortWeapon->SetupAttachment(GetMesh(), TEXT("joint49_socket"));

	DisposableWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisposableWeapon"));
	DisposableWeapon->SetupAttachment(GetMesh(), TEXT("joint49_socket"));

	LongWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LongWeapon"));
	LongWeapon->SetupAttachment(GetMesh(), TEXT("joint49_socket"));

	WeaponNow = EItemType::NoWeapon;//
}

void AWMACharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnHpZero.AddUObject(this, &AWMACharacterBase::SetDead);
}

void AWMACharacterBase::CloseAttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);


	//float AttackRange;
	//switch (WeaponNow)//
	//{
	//case EItemType::ShortWeapon:
	//	AttackRange = Stat->GetCharacterStat().ShortWPRange;
	//	break;
	//case EItemType::DisposableWeapon:
	//	AttackRange = Stat->GetCharacterStat().DisposableWPRange;
	//	break;
	//case EItemType::LongWeapon:
	//	AttackRange = Stat->GetCharacterStat().LongWPRange;
	//	break;
	//case EItemType::NoWeapon:
	//	AttackRange = 0.0f;
	//	break;
	//default:
	//	AttackRange = 0.0f;
	//	break;
	//}
	//

	const float AttackRange = Stat->GetCharacterStat().ShortWPRange;
	const float AttackRadius = Stat->GetAttackRadius();
	const float AttackDamage = Stat->GetCharacterStat().Attack;
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_WMAACTION, FCollisionShape::MakeSphere(AttackRadius), Params);
	
	if (HitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG

	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;	// 충돌하면 녹색, 아니면 적색

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f); // 5초동안 그리기
#endif
}

float AWMACharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->ApplyDamage(DamageAmount);
	
	//SetDead();

	return DamageAmount;
}

void AWMACharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);	// 움직이지 못하게 하기
	PlayDeadAnimation();
	SetActorEnableCollision(false);
}

void AWMACharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage, 1.0f);
}

int32 AWMACharacterBase::GetName()
{
	return Stat->GetCurrentName();
}

void AWMACharacterBase::SetName(int32 InNewName)
{
	Stat->SetNameStat(InNewName);
}

void AWMACharacterBase::TakeItem(UABItemData* InItemData)
{
	if (InItemData) {
		TakeItemActions[(uint8)InItemData->Type].ItemDelegate.ExecuteIfBound(InItemData);
	}
}

void AWMACharacterBase::EquipShort(UABItemData* InItemData)
{
	UABWeaponItemData* WeaponItemData = Cast<UABWeaponItemData>(InItemData);
	UWMAGameInstance* InteractionItem = Cast<UWMAGameInstance>(GetWorld()->GetGameInstance());
	
	if (WeaponItemData && InteractionItem->InteractItem) {
		ShortWeapon->SetHiddenInGame(false);
		DisposableWeapon->SetHiddenInGame(true);
		LongWeapon->SetHiddenInGame(true);

		ShortWeapon->SetStaticMesh(WeaponItemData->ShortWeaponMesh);

		WeaponNow = EItemType::ShortWeapon;										// 현재 들고 있는 무기 변경

	}

	//UE_LOG(LogTemplateCharacter, Log, TEXT("EQUIP Short"));
}

void AWMACharacterBase::EquipDisposable(UABItemData* InItemData)
{
	UABWeaponItemData* WeaponItemData = Cast<UABWeaponItemData>(InItemData);
	if (WeaponItemData) {
		ShortWeapon->SetHiddenInGame(true);
		DisposableWeapon->SetHiddenInGame(false);
		LongWeapon->SetHiddenInGame(true);

		DisposableWeapon->SetStaticMesh(WeaponItemData->DisposableWeaponMesh);

		WeaponNow = EItemType::DisposableWeapon;								// 현재 들고 있는 무기 변경
	}


	UE_LOG(LogTemplateCharacter, Log, TEXT("EQUIP DISPOSABLE"));
	//UE_LOG(LogTemplateCharacter, Log, TEXT("EQUIP DISPOSABLE"));
}

void AWMACharacterBase::EquipLong(UABItemData* InItemData)
{
	UABWeaponItemData* WeaponItemData = Cast<UABWeaponItemData>(InItemData);
	if (WeaponItemData) {
		ShortWeapon->SetHiddenInGame(true);
		DisposableWeapon->SetHiddenInGame(true);
		LongWeapon->SetHiddenInGame(false);

		LongWeapon->SetStaticMesh(WeaponItemData->LongWeaponMesh);

		WeaponNow = EItemType::LongWeapon;								// 현재 들고 있는 무기 변경
	}


	UE_LOG(LogTemplateCharacter, Log, TEXT("EQUIP LONG"));
	//UE_LOG(LogTemplateCharacter, Log, TEXT("EQUIP LONG"));
}

//// Called when the game starts or when spawned
//void AWMACharacterBase::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void AWMACharacterBase::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void AWMACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

