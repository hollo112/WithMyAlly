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
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));
	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("Owner: %s"), *OwnerActor->GetName());
	}
	else
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("No Owner"));
	}

	Super::PossessedBy(NewController);

	OwnerActor = GetOwner();
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
				ServerRPCCloseAttack();
				/*bCanAttack = false;
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

				FTimerHandle Handle;
				GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
					{
						bCanAttack = true;
						GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
					}
				), CloseAttackTime, false, -1.0f);

				UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
				AnimInstance->Montage_Play(ComboActionMontage);*/
			}
		}
	}
}

void AWMACharacterPlayer::CloseAttackHitCheck()
{
	if (HasAuthority())
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
}

bool AWMACharacterPlayer::ServerRPCCloseAttack_Validate()
{
	return true;
}

void AWMACharacterPlayer::ServerRPCCloseAttack_Implementation()
{
	MulticastRPCCloseAttack();
}

void AWMACharacterPlayer::MulticastRPCCloseAttack_Implementation()
{
	if (HasAuthority())
	{
		bCanAttack = false;
		OnRep_CanCloseAttack();

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
			{
				bCanAttack = true;
				OnRep_CanCloseAttack();
			}
		), CloseAttackTime, false, -1.0f);
	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage);
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
		return;
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

