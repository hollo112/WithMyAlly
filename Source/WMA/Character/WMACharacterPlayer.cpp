// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WMACharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WMAComboActionData.h"
#include "CharacterStat/WMACharacterStatComponent.h"
#include "WMACharacterControlData.h"
#include "WMA.h"
#include "Components/CapsuleComponent.h"
#include "Physics/WMACollsion.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameStateBase.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerState.h"
#include "Engine/AssetManager.h"
#include "GameData/WMAGameInstance.h"
#include "Interface/WMAGameInterface.h"
#include "Item/ABItemBat.h"	
#include "Components/BoxComponent.h"
#include "UI/WMAWidgetAttacked1.h"


AWMACharacterPlayer::AWMACharacterPlayer()
{
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 150.0f;
	CameraBoom->TargetOffset = FVector(0.0, 0.0, 70.0);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	MyBat = CreateDefaultSubobject<AABItemBat>(TEXT("Bat"));

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Attack.IA_Attack'"));
	if (nullptr != InputActionAttackRef.Object)
	{
		AttackAction = InputActionAttackRef.Object;
	}

	bCanAttack = true;

	//Female Hair
	FName HairSocket(TEXT("HairSocket"));
	if (GetMesh()->DoesSocketExist(HairSocket)) 
	{
		Hair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hair"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> HairMesh(TEXT("/Script/Engine.StaticMesh'/Game/MyCharacters/NewFemale/NewHair.NewHair'"));
		if (HairMesh.Succeeded())
		{
			// 스태틱 메시를 설정해주고
			Hair->SetStaticMesh(HairMesh.Object);
		}
		Hair->SetupAttachment(GetMesh(), HairSocket);
	}
}

void AWMACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		EnableInput(PlayerController);
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
	}

	SetCharacterControl();

// Stat
	Stat->SetCurrentHp(Stat->GetCharacterStat().MaxHp);
	GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed;
}

void AWMACharacterPlayer::SetDead()
{
	Super::SetDead();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		DisableInput(PlayerController);
	}
}

void AWMACharacterPlayer::PossessedBy(AController* NewController)
{
	/*WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));
	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("Owner: %s"), *OwnerActor->GetName());
	}
	else
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("No Owner"));
	}*/

	Super::PossessedBy(NewController);

	/*OwnerActor = GetOwner();
	if (OwnerActor)
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("Owner: %s"), *OwnerActor->GetName());
	}
	else
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("No Owner"));
	}

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));*/
	//UpdateMeshesFromPlayerState();
	UpdateAnimInstance();
}

void AWMACharacterPlayer::OnRep_Owner()
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::OnRep_Owner();

	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("Owner: %s"), *OwnerActor->GetName());
	}
	else
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("No Owner"));
	}

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
}

void AWMACharacterPlayer::PostNetInit()
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostNetInit();

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
}

void AWMACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWMACharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWMACharacterPlayer::Look);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AWMACharacterPlayer::Attack);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AWMACharacterPlayer::SprintHold);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AWMACharacterPlayer::SprintRelease);

	PlayerInputComponent->BindAction("Attacked1", IE_Pressed, this, &AWMACharacterPlayer::StartAttacked1);
	PlayerInputComponent->BindAction("Attacked1", IE_Released, this, &AWMACharacterPlayer::StopAttacked1);

	PlayerInputComponent->BindAction("Attacked2", IE_Pressed, this, &AWMACharacterPlayer::StartAttacked2);
	PlayerInputComponent->BindAction("Attacked2", IE_Released, this, &AWMACharacterPlayer::StopAttacked2);

	PlayerInputComponent->BindAction("Attacked3", IE_Pressed, this, &AWMACharacterPlayer::StartAttacked3);
	PlayerInputComponent->BindAction("Attacked3", IE_Released, this, &AWMACharacterPlayer::StopAttacked3);



	// 무기 교체 Input
	InputComponent->BindAction("ChangeWeapon_Short_1", EInputEvent::IE_Released, this, &AWMACharacterPlayer::ChangeWeapon_Short);

	InputComponent->BindAction("ChangeWeapon_Disposable_2", EInputEvent::IE_Released, this, &AWMACharacterPlayer::ChangeWeapon_Disposable);

	InputComponent->BindAction("ChangeWeapon_Long_3", EInputEvent::IE_Released, this, &AWMACharacterPlayer::ChangeWeapon_Long);
}


void AWMACharacterPlayer::SetCharacterControl()
{
	if (!IsLocallyControlled())
	{
		UE_LOG(LogTemp, Log, TEXT("clientIn"));
		return;
	}

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
	}

}

void AWMACharacterPlayer::SetCharacterControlData(const UWMACharacterControlData* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
}

void AWMACharacterPlayer::Move(const FInputActionValue& Value)
{
	if (!bCanAttack)
	{
		return;
	}

	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AWMACharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AWMACharacterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWMACharacterPlayer, bCanAttack);
}

void AWMACharacterPlayer::Attack()
{
	if (!GetMovementComponent()->IsFalling())
	{
		if (WeaponNow != EItemType::NoWeapon)
		{
			//ProcessComboCommand();
			if (bCanAttack)
			{
				if (!HasAuthority())				// 클라에서 동작
				{
					bCanAttack = false;
					GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

					FTimerHandle Handle;
					GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
						{
							bCanAttack = true;
							GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
						}
					), CloseAttackTime, false, -1.0f);

					PlayCloseAttackAnimation();
				}
				ServerRPCCloseAttack(GetWorld()->GetGameState()->GetServerWorldTimeSeconds());			// 서버의 시간 클라에게 넘겨주기
				
			}
		}
	}
}

void AWMACharacterPlayer::PlayCloseAttackAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(ComboActionMontage);
}

void AWMACharacterPlayer::CloseAttackHitCheck()
{
	if (IsLocallyControlled())
	{
		FHitResult OutHitResult;
		FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

		float AttackRange;
		switch (WeaponNow)//
		{
		case EItemType::ShortWeapon:
			AttackRange = Stat->GetCharacterStat().ShortWPRange;
			break;
		case EItemType::DisposableWeapon:
			AttackRange = Stat->GetCharacterStat().DisposableWPRange;
			break;
		case EItemType::LongWeapon:
			AttackRange = Stat->GetCharacterStat().LongWPRange;
			break;
		case EItemType::NoWeapon:
			AttackRange = 0.0f;
			break;
		default:
			AttackRange = 0.0f;
			break;
		}
		const float AttackRadius = Stat->GetAttackRadius();
		const float AttackDamage = Stat->GetCharacterStat().Attack;
		const FVector Forward = GetActorForwardVector();
		const FVector Start = GetActorLocation() + Forward * GetCapsuleComponent()->GetScaledCapsuleRadius();
		const FVector End = Start + GetActorForwardVector() * AttackRange;

		bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_WMAACTION, FCollisionShape::MakeSphere(AttackRadius), Params);


		//if (OutHitResult.GetActor()->IsA(AWMACharacterPlayer::StaticClass()))			//만약 플레이러를 공격했다면 판정X
		//{
		//	HitDetected = false;
		//}

		float HitCheckTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
		if (!HasAuthority())
		{
			if (HitDetected)
			{
				ServerRPCNotifyHit(OutHitResult, HitCheckTime);
				FDamageEvent DamageEvent;
				OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
			}
			else
			{
				ServerRPCNotifyMiss(Start, End, Forward, HitCheckTime);
			}
		}
		else
		{
			FColor DebugColor = HitDetected ? FColor::Green : FColor::Red;
			DrawDebugAttackRange(DebugColor, Start, End, Forward);
			if (HitDetected)
			{
				AttackHitConfirm(OutHitResult.GetActor());
			}
		}
	}
}

void AWMACharacterPlayer::AttackHitConfirm(AActor* HitActor)
{
	if (HasAuthority())
	{
		const float AttackDamage = Stat->GetCharacterStat().Attack;
		FDamageEvent DamageEvent;
		HitActor->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	}
}

void AWMACharacterPlayer::DrawDebugAttackRange(const FColor& DrawColor, FVector TraceStart, FVector TraceEnd, FVector Forward)
{
#if ENABLE_DRAW_DEBUG

	float AttackRange;
	switch (WeaponNow)//
	{
	case EItemType::ShortWeapon:
		AttackRange = Stat->GetCharacterStat().ShortWPRange;
		break;
	case EItemType::DisposableWeapon:
		AttackRange = Stat->GetCharacterStat().DisposableWPRange;
		break;
	case EItemType::LongWeapon:
		AttackRange = Stat->GetCharacterStat().LongWPRange;
		break;
	case EItemType::NoWeapon:
		AttackRange = 0.0f;
		break;
	default:
		AttackRange = 0.0f;
		break;
	}

	const float AttackRadius = Stat->GetAttackRadius();

	FVector CapsuleOrigin = TraceStart + (TraceEnd - TraceStart) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	// 충돌하면 녹색, 아니면 적색

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor, false, 5.0f); // 5초동안 그리기
#endif
}

bool AWMACharacterPlayer::ServerRPCCloseAttack_Validate(float AttackStartTime)
{
	if (LastCloseAttackStartTime == 0.0f)
	{
		return true;
	}

	return (AttackStartTime - LastCloseAttackStartTime) > (CloseAttackTime - 0.4f);
}

void AWMACharacterPlayer::ServerRPCCloseAttack_Implementation(float AttackStartTime)
{
	bCanAttack = false;
	OnRep_CanCloseAttack();

	float AttackTimeDifference = GetWorld()->GetTimeSeconds() - AttackStartTime;		// 서버의 시간에서 클라가 보낸시간을 뺀다
	AttackTimeDifference = FMath::Clamp(AttackTimeDifference, 0.0f, CloseAttackTime - 0.01f);

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
		{
			bCanAttack = true;
			OnRep_CanCloseAttack();
		}
	), CloseAttackTime - AttackTimeDifference, false, -1.0f);

	LastCloseAttackStartTime = AttackStartTime;

	PlayCloseAttackAnimation();

	MulticastRPCCloseAttack();
	//for (APlayerController* PlayerController : TActorRange<APlayerController>(GetWorld()))
	//{
	//	if (PlayerController && GetController() != PlayerController)			// 나와 다른 컨트롤러
	//	{
	//		if (!PlayerController->IsLocalController())
	//		{
	//			// Simulated Proxy로 폰을 재생하는 PlayerController
	//			AWMACharacterPlayer* OtherPlayer = Cast<AWMACharacterPlayer>(PlayerController->GetPawn());
	//			if (OtherPlayer)
	//			{
	//				OtherPlayer->ClientRPCPlayAnimation(this);
	//			}
	//		}
	//	}
	//}
}

void AWMACharacterPlayer::MulticastRPCCloseAttack_Implementation()
{
	if (!IsLocallyControlled())
	{
		PlayCloseAttackAnimation();
	}
}


bool AWMACharacterPlayer::ServerRPCNotifyHit_Validate(const FHitResult& HitResult, float HitCheckTime)
{
	return (HitCheckTime - LastCloseAttackStartTime) > AcceptMinCheckTime;
}

void AWMACharacterPlayer::ServerRPCNotifyHit_Implementation(const FHitResult& HitResult, float HitCheckTime)
{
	AActor* HitActor = HitResult.GetActor();
	if (::IsValid(HitActor))
	{
		const FVector HitLocation = HitResult.Location;
		const FBox HitBox = HitActor->GetComponentsBoundingBox();
		const FVector ActorBoxCenter = (HitBox.Min + HitBox.Max) * 0.5f;
		if (FVector::DistSquared(HitLocation, ActorBoxCenter) <= AcceptCheckDistance * AcceptCheckDistance)
		{
			AttackHitConfirm(HitActor);
		}
		else
		{
			WMA_LOG(LogWMANetwork, Warning, TEXT("%s"), TEXT("Hit Rejected"));
		}

#if ENABLE_DRAW_DEBUG
		DrawDebugPoint(GetWorld(), ActorBoxCenter, 50.0f, FColor::Cyan, false, 5.0f);
		DrawDebugPoint(GetWorld(), HitLocation, 50.0f, FColor::Magenta, false, 5.0f);
#endif
		DrawDebugAttackRange(FColor::Green, HitResult.TraceStart, HitResult.TraceEnd, HitActor->GetActorForwardVector());
	}
}

bool AWMACharacterPlayer::ServerRPCNotifyMiss_Validate(FVector_NetQuantize TraceStart, FVector_NetQuantize TraceEnd, FVector_NetQuantizeNormal TraceDir, float HitCheckTime)
{
	return (HitCheckTime - LastCloseAttackStartTime) > AcceptMinCheckTime;
}

void AWMACharacterPlayer::ServerRPCNotifyMiss_Implementation(FVector_NetQuantize TraceStart, FVector_NetQuantize TraceEnd, FVector_NetQuantizeNormal TraceDir, float HitCheckTime)
{
	DrawDebugAttackRange(FColor::Red, TraceStart, TraceEnd, TraceDir);
}

void AWMACharacterPlayer::OnRep_CanCloseAttack()
{
	if (!bCanAttack)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void AWMACharacterPlayer::ChangeWeapon_Short()
{
	if (WeaponNow == EItemType::NoWeapon) {
		//return;
	}

	ShortWeapon->SetHiddenInGame(false);
	DisposableWeapon->SetHiddenInGame(true);
	LongWeapon->SetHiddenInGame(true);

	WeaponNow = EItemType::ShortWeapon;									// 현재 들고 있는 무기 변경

	//UE_LOG(LogTemplateCharacter, Log, TEXT("EQUIP Short"));
}

void AWMACharacterPlayer::ChangeWeapon_Disposable()
{
	if (WeaponNow == EItemType::NoWeapon) {
		return;
	}

	ShortWeapon->SetHiddenInGame(true);
	DisposableWeapon->SetHiddenInGame(false);
	LongWeapon->SetHiddenInGame(true);

	WeaponNow = EItemType::DisposableWeapon;							// 현재 들고 있는 무기 변경

	//UE_LOG(LogTemplateCharacter, Log, TEXT("EQUIP DISPOSABLE"));
}

void AWMACharacterPlayer::ChangeWeapon_Long()
{
	ShortWeapon->SetHiddenInGame(true);
	DisposableWeapon->SetHiddenInGame(true);
	LongWeapon->SetHiddenInGame(false);

	WeaponNow = EItemType::LongWeapon;									// 현재 들고 있는 무기 변경

	//UE_LOG(LogTemplateCharacter, Log, TEXT("EQUIP LONG"));
}

//void AWMACharacterPlayer::UpdateMeshesFromPlayerState()
//{
//	int32 MeshIndex = FMath::Clamp(GetPlayerState()->PlayerId % PlayerMeshes.Num(), 0, PlayerMeshes.Num() - 1);
//	MeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(PlayerMeshes[MeshIndex], FStreamableDelegate::CreateUObject(this, &AWMACharacterBase::MeshLoadCompleted));
//}

void AWMACharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!HasAuthority())
	{
		if (IsLocallyControlled())
		{
			auto SM_Male = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/MyCharacters/Male/Male_Idle.Male_Idle"));
			if (SM_Male)
			{
				GetMesh()->SetSkeletalMesh(SM_Male);
			}

			auto ABPClass = LoadClass<UAnimInstance>(NULL, TEXT("/Game/MyCharacters/Male/Animation/ABP_Male.ABP_Male_C"));
			GetMesh()->SetAnimInstanceClass(ABPClass);

			auto AMClass = LoadObject<UAnimMontage>(NULL, TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Male/Animation/AM_MaleComboAttack.AM_MaleComboAttack'"));
			if (AMClass)
			{
				ComboActionMontage = AMClass;
			}
		}
	}
}

void AWMACharacterPlayer::UpdateAnimInstance()
{
	if (!IsLocallyControlled())
	{
		auto SM_Male = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/MyCharacters/Male/Male_Idle.Male_Idle"));
		if (SM_Male)
		{
			GetMesh()->SetSkeletalMesh(SM_Male);
		}

		auto ABPClass = LoadClass<UAnimInstance>(NULL, TEXT("/Game/MyCharacters/Male/Animation/ABP_Male.ABP_Male_C"));
		GetMesh()->SetAnimInstanceClass(ABPClass);

		auto AMClass = LoadObject<UAnimMontage>(NULL, TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Male/Animation/AM_MaleComboAttack.AM_MaleComboAttack'"));
		if (AMClass)
		{
			ComboActionMontage = AMClass;
		}
	}
}

void AWMACharacterPlayer::ServerSprint_Implementation(bool isSprinting)
{
	MulticastSprint(isSprinting);
}

void AWMACharacterPlayer::MulticastSprint_Implementation(bool isSprinting)
{
	if (isSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed *= 2;  // 원하는 속도배수로 조정
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed /= 2;  // 증가했던 속도를 원래대로 복원
	}
}

void AWMACharacterPlayer::SprintHold()
{
	bIsHoldingSprintButton = true;
	if (bIsHoldingSprintButton)
	{
		ServerSprint(bIsHoldingSprintButton);
	}
}

void AWMACharacterPlayer::SprintRelease()
{
	bIsHoldingSprintButton = false;
	ServerSprint(false);
}

void AWMACharacterPlayer::StartAttacked1()
{	
	StartAttack1 = 1;

	UpdateAttackedIMG();
}

void AWMACharacterPlayer::StopAttacked1()
{
	StartAttack1 = 0;
	//UE_LOG(LogTemp, Warning, TEXT("%d"), StartAttack1);
}

void AWMACharacterPlayer::StartAttacked2()
{
	StartAttack2 = 1;

	UpdateAttackedIMG();
}

void AWMACharacterPlayer::StopAttacked2()
{
	StartAttack2 = 0;
}

void AWMACharacterPlayer::StartAttacked3()
{
	StartAttack3 = 1;

	UpdateAttackedIMG();
}

void AWMACharacterPlayer::StopAttacked3()
{
	StartAttack3 = 0;
}

