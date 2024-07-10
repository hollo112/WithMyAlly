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
#include "Item/ABDoor.h"	
#include "Item/ABItemFruitSwd.h"
#include "Item/EV_ButtonActor.h"	
#include "Item/WMACardRead.h"
#include "Item/ABItemSiren.h"
#include "Item/ABThorwItem.h"
#include "Item/ABItemGun.h"
#include "Item/WMAFireExtinguisher.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WMAWidgetAttacked1.h"
#include "Game/WMAGameModeBase.h"
#include "Animation/WMAAnimInstance.h"
#include <Blueprint/WidgetLayoutLibrary.h>


AWMACharacterPlayer::AWMACharacterPlayer()
{
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 150.0f;
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

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionESCRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_ESCMenu.IA_ESCMenu'"));
	if (nullptr != InputActionESCRef.Object)
	{
		ESCAction = InputActionESCRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionCrouchRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Crouch.IA_Crouch'"));
	if (nullptr != InputActionCrouchRef.Object)
	{
		CrouchAction = InputActionCrouchRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionThrowRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Throw.IA_Throw'"));
	if (nullptr != InputActionCrouchRef.Object)
	{
		ThrowAction = InputActionThrowRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLMouseRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_LMouse.IA_LMouse'"));
	if (nullptr != InputActionLMouseRef.Object)
	{
		LMouseAction = InputActionLMouseRef.Object;
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

	//ESC Widget
	static ConstructorHelpers::FClassFinder<UUserWidget> ESCWid(TEXT("/Game/UI/WBP_ESCMenu.WBP_ESCMenu_C"));
	if (ESCWid.Succeeded())
	{
		ESCMenuWidgetClass = ESCWid.Class;
	}


	//Stabbing Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> StabbingMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Male/Animation/AM_MaleStabbing.AM_MaleStabbing'"));
	if (StabbingMontageRef.Object)
	{
		StabbingMontage = StabbingMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PreThrowMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Male/Animation/AM_Male_PreThrow_Montage.AM_Male_PreThrow_Montage'"));
	if (PreThrowMontageRef.Object)
	{
		PreThrowMontage = PreThrowMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> PostThrowMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Male/Animation/AM_Male_PostThrow_Montage.AM_Male_PostThrow_Montage'"));
	if (PostThrowMontageRef.Object)
	{
		PostThrowMontage = PostThrowMontageRef.Object;
	}

	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MGunShootingMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Male/Animation/AM_Male_Firing_Rifle_Montage.AM_Male_Firing_Rifle_Montage'"));
	if (MGunShootingMontageRef.Object)
	{
		MShootingMontage = MGunShootingMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FGunShootingMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/NewFemale/Animation/AM_Female_Firing_Rifle_Montage.AM_Female_Firing_Rifle_Montage'"));
	if (FGunShootingMontageRef.Object)
	{
		FShootingMontage = FGunShootingMontageRef.Object;
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

// ESCUI
	ESCWidget = CreateWidget<UUserWidget>(GetWorld(), ESCMenuWidgetClass);
	if (ESCWidget)
	{
		ESCWidget->AddToViewport();
	}
//
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);

	if (CurrentLevelName == "NewMap")
	{
		SetActorScale3D(FVector(1.7, 1.7, 1.7));
		CameraBoom->TargetArmLength = 200.0f;
		CameraBoom->TargetOffset = FVector(0.0, 0.0, 85.0);
		GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed * 1.7;
	}
	else if (CurrentLevelName == "WithMyAlly15f")
	{
		CameraBoom->TargetArmLength = 150.0f;
		SetActorScale3D(FVector(1.2, 1.2, 1.2));
	}

// Crouch
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AWMACharacterPlayer::SetDead()
{
	Super::SetDead();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		DisableInput(PlayerController);
	}

	FTimerHandle TimerHandle;
	float DeadTime = 1.2;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			AWMAGameModeBase* GameMode = Cast<AWMAGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (GameMode)
			{
				UE_LOG(LogTemp, Log, TEXT("Log Travel"));
				//GameMode->bUseSeamlessTravel = true;
				GameMode->Travel15F();
			}
		}), DeadTime, false);
}

void AWMACharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

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
	EnhancedInputComponent->BindAction(ESCAction, ETriggerEvent::Triggered, this, &AWMACharacterPlayer::ESCInput);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AWMACharacterPlayer::StartCrouch);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AWMACharacterPlayer::StopCrouch);
	EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &AWMACharacterPlayer::StartThrow);
	EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Completed, this, &AWMACharacterPlayer::StopThrow);
	EnhancedInputComponent->BindAction(LMouseAction, ETriggerEvent::Triggered, this, &AWMACharacterPlayer::LMouseClick);


	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AWMACharacterPlayer::SprintHold);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AWMACharacterPlayer::SprintRelease);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AWMACharacterPlayer::InteractHold);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &AWMACharacterPlayer::InteractRelease);

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
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 25.f;
}

void AWMACharacterPlayer::ESCInput()
{
	ServerESC();
}

void AWMACharacterPlayer::ServerESC_Implementation()
{
	MulticastESC();
}

void AWMACharacterPlayer::MulticastESC_Implementation()
{
	if (!bIsESCOpened)
	{
		if (ESCWidget)
		{	
			if (IsLocallyControlled())
			{
				UE_LOG(LogTemp, Log, TEXT("Log Message"));
				bIsESCOpened = true;
				ESCWidget->SetVisibility(ESlateVisibility::Visible);
				APlayerController* PlayerController = Cast<APlayerController>(GetController());
				if (PlayerController)
				{
					PlayerController->bShowMouseCursor = true;
				}
			}
		}
	}
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

	//Sound
	if (HasAuthority())
	{
		const float MinSoundThreshold = 50.0f; // 예시 임계값

		if (!bIsHoldingSprintButton && !bIsHoldingCrouchButton) {
			UE_LOG(LogTemp, Warning, TEXT("dB 70"));
			const float SoundStrength = 40.0f;
			if (SoundStrength >= MinSoundThreshold) {
				AISenseHearing->ReportNoiseEvent(this, GetActorLocation(), SoundStrength, this, 20.0f, FName("WalkStep"));
			}
		}
		else {
			if (!bIsHoldingCrouchButton)
			{
				UE_LOG(LogTemp, Warning, TEXT("dB 120"));
				const float SoundStrength = 120.0f;
				if (SoundStrength >= MinSoundThreshold) {
					AISenseHearing->ReportNoiseEvent(this, GetActorLocation(), SoundStrength, this, 600.0f, FName("RunStep"));
				}
			}		
		}
	}
	
	if (!HasAuthority())
	{
		FVector ClientPosition = GetActorLocation();
		ServerRPCMovingSound(ClientPosition, bIsHoldingSprintButton, bIsHoldingCrouchButton);
	}
}

void AWMACharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AWMACharacterPlayer::StartCrouch()
{
	bIsHoldingCrouchButton = true;
	Crouch();
}

void AWMACharacterPlayer::StopCrouch()
{
	bIsHoldingCrouchButton = false;
	UnCrouch();
}

void AWMACharacterPlayer::StartThrow()
{	
	if (WeaponNow == EItemType::ThrowItem)
	{
		if (bIsHoldingThrowButton == false)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			AnimInstance->StopAllMontages(0.0f);


			AnimInstance->Montage_Play(PreThrowMontage);


			bIsHoldingThrowButton = true;
		}
	}
}

void AWMACharacterPlayer::StopThrow()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	bIsHoldingThrowButton = false;


	if (WeaponNow == EItemType::ThrowItem)
	{
		AnimInstance->Montage_Play(PostThrowMontage);

		ThrowItem->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		ThrowItem->SetSimulatePhysics(true);
		FVector ForwardVector = GetActorForwardVector();
		FVector Impulse = ForwardVector * 500.0f + FVector(0.0f, 0.0f, 300.0f);
		ThrowItem->AddImpulse(Impulse, "ThrowItem", true);
	
		SetActorEnableCollision(true);

	}

	if (bIsHoldingThrowButton == false)
	{
		WeaponNow = EItemType::NoWeapon;
	}

}


void AWMACharacterPlayer::LMouseClick()
{
	//FireExtinguisher
	class AWMAFireExtinguisher* FireExt;
	FireExt = Cast<AWMAFireExtinguisher>(UGameplayStatics::GetActorOfClass(GetWorld(), AWMAFireExtinguisher::StaticClass()));
	if (FireExt)
	{
		if (FireExt->bIsHolding)
		{
			FireExt->TurnOnFireExt();
			bIsHoldingRifle = true;	// 임시
			UWMAAnimInstance* AnimInstance = Cast<UWMAAnimInstance>(GetMesh()->GetAnimInstance());// 임시
			AnimInstance->bIsHoldingRifle = true; // 임시
		}
	}
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
		if (WeaponNow == EItemType::DisposableWeapon || WeaponNow == EItemType::ShortWeapon)
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

		else if (WeaponNow == EItemType::Gun)
		{
			if (bCanAttack) {

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
					), CloseShootAttackTime, false, -1.0f);

					PlayGunShootingAnimation();
				}
				ServerRPCGunShooting(GetWorld()->GetGameState()->GetServerWorldTimeSeconds());			// 서버의 시간 클라에게 넘겨주기
			}
		}

	}

}

void AWMACharacterPlayer::PlayCloseAttackAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);

	if (WeaponNow == EItemType::ShortWeapon)
	{
		AnimInstance->Montage_Play(ComboActionMontage);
	}
	else if (WeaponNow == EItemType::DisposableWeapon)
	{
		AnimInstance->Montage_Play(StabbingMontage);
	}
}

void AWMACharacterPlayer::PlayGunShootingAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	if (WeaponNow == EItemType::Gun)
	{
		if (HasAuthority())
		{
			AnimInstance->Montage_Play(FShootingMontage);
		}
		else
		{
			AnimInstance->Montage_Play(MShootingMontage);
		}
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

	//DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor, false, 5.0f); // 5초동안 그리기
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
}

bool AWMACharacterPlayer::ServerRPCGunShooting_Validate(float AttackStartTime)
{
	if (LastCloseAttackStartTime == 0.0f)
	{
		return true;
	}

	return (AttackStartTime - LastCloseAttackStartTime) > (CloseShootAttackTime);
}

void AWMACharacterPlayer::ServerRPCGunShooting_Implementation(float AttackStartTime)
{
	bCanAttack = false;
	OnRep_CanCloseAttack();

	float AttackTimeDifference = GetWorld()->GetTimeSeconds() - AttackStartTime;		// 서버의 시간에서 클라가 보낸시간을 뺀다
	AttackTimeDifference = FMath::Clamp(AttackTimeDifference, 0.0f, CloseShootAttackTime - 0.01f);

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
		{
			bCanAttack = true;
			OnRep_CanCloseAttack();
		}
	), CloseShootAttackTime - AttackTimeDifference, false, -1.0f);

	LastCloseAttackStartTime = AttackStartTime;

	PlayGunShootingAnimation();

	MulticastRPCGunShooting();
}

void AWMACharacterPlayer::MulticastRPCCloseAttack_Implementation()
{
	if (!IsLocallyControlled())
	{
		PlayCloseAttackAnimation();
	}
}

void AWMACharacterPlayer::MulticastRPCGunShooting_Implementation()
{
	if (!IsLocallyControlled())
	{
		PlayGunShootingAnimation();
	}
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
	//if (WeaponNow == EItemType::NoWeapon) {
	//	//return;
	//}

	//ShortWeapon->SetHiddenInGame(false);
	//DisposableWeapon->SetHiddenInGame(true);
	//LongWeapon->SetHiddenInGame(true);

	//WeaponNow = EItemType::ShortWeapon;									// 현재 들고 있는 무기 변경

	ServerRPCChangeWP(EItemType::ShortWeapon);
}

void AWMACharacterPlayer::ChangeWeapon_Disposable()
{
	//if (WeaponNow == EItemType::NoWeapon) {
	//	return;
	//}

	//ShortWeapon->SetHiddenInGame(true);
	//DisposableWeapon->SetHiddenInGame(false);
	//LongWeapon->SetHiddenInGame(true);

	//WeaponNow = EItemType::DisposableWeapon;							// 현재 들고 있는 무기 변경
	ServerRPCChangeWP(EItemType::DisposableWeapon);
}

void AWMACharacterPlayer::ChangeWeapon_Long()
{
	ShortWeapon->SetHiddenInGame(true);
	DisposableWeapon->SetHiddenInGame(true);
	LongWeapon->SetHiddenInGame(false);

	WeaponNow = EItemType::LongWeapon;									// 현재 들고 있는 무기 변경
}

void AWMACharacterPlayer::ServerRPCChangeWP_Implementation(EItemType InItemData)
{
	MulticastRPCChangeWP(InItemData);
}

void AWMACharacterPlayer::MulticastRPCChangeWP_Implementation(EItemType InItemData)
{
	if (WeaponNow == EItemType::NoWeapon) {
		return;
	}

	if (InItemData == EItemType::DisposableWeapon)
	{
		ShortWeapon->SetHiddenInGame(true);
		DisposableWeapon->SetHiddenInGame(false);
		LongWeapon->SetHiddenInGame(true);
		ThrowItem->SetHiddenInGame(true);

		WeaponNow = EItemType::DisposableWeapon;
	}

	if (InItemData == EItemType::ShortWeapon)
	{
		ShortWeapon->SetHiddenInGame(false);
		DisposableWeapon->SetHiddenInGame(true);
		LongWeapon->SetHiddenInGame(true);
		ThrowItem->SetHiddenInGame(true);

		WeaponNow = EItemType::ShortWeapon;								// 현재 들고 있는 무기 변경
	}

	if (InItemData == EItemType::ThrowItem)
	{
		ShortWeapon->SetHiddenInGame(true);
		DisposableWeapon->SetHiddenInGame(true);
		LongWeapon->SetHiddenInGame(true);
		ThrowItem->SetHiddenInGame(false);


		WeaponNow = EItemType::ThrowItem;
	}
}

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

			Hair->SetHiddenInGame(true);
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

		Hair->SetHiddenInGame(true);
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

void AWMACharacterPlayer::InteractHold()
{
	/*class AEV_ButtonActor* EVButton;
	EVButton = Cast<AEV_ButtonActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AEV_ButtonActor::StaticClass()));
	if (EVButton)
	{
		EVButton->OnInteract();
	}*/

	TArray<AActor*> Result;
	GetOverlappingActors(Result, AActor::StaticClass());

	for (auto* TmpActor : Result)
	{
		if (TmpActor->IsA(AEV_ButtonActor::StaticClass()))
		{
			AEV_ButtonActor* EVButton = Cast<AEV_ButtonActor>(TmpActor);
			EVButton->OnInteract();
		}
	}

	class AWMACardRead* CardRead;
	CardRead = Cast<AWMACardRead>(UGameplayStatics::GetActorOfClass(GetWorld(), AWMACardRead::StaticClass()));
	if (CardRead)
	{
		CardRead->OnInteract();
	}
	

	ServerRPCPickUp();
}

void AWMACharacterPlayer::InteractRelease()
{

}

void AWMACharacterPlayer::ServerRPCPickUp_Implementation()
{
	MulticastRPCPickUp();
}

void AWMACharacterPlayer::MulticastRPCPickUp_Implementation()
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, AActor::StaticClass());

	for (auto* TmpActor : Result)
	{
		if (TmpActor->IsA(AABItemBat::StaticClass()))
		{
			AABItemBat* Bat = Cast<AABItemBat>(TmpActor);
			Bat->OnInteract();
			Bat->Destroy();
		}

		if (TmpActor->IsA(AABItemFruitSwd::StaticClass()))
		{
			AABItemFruitSwd* Bat = Cast<AABItemFruitSwd>(TmpActor);
			Bat->OnInteract();
			Bat->Destroy();
		}

		if (TmpActor->IsA(AABDoor::StaticClass()))
		{
			AABDoor* Door = Cast<AABDoor>(TmpActor);
			Door->OnInteract();
		}

		if (TmpActor->IsA(AABThorwItem::StaticClass()))
		{
			AABThorwItem* Samdasoo = Cast<AABThorwItem>(TmpActor);
			Samdasoo->OnInteract();
			Samdasoo->Destroy();
		}

		if (TmpActor->IsA(AABItemGun::StaticClass()))
		{
			AABItemGun* M16 = Cast<AABItemGun>(TmpActor);
			M16->OnInteract();
			M16->Destroy();
			UWMAAnimInstance* AnimInstance = Cast<UWMAAnimInstance>(GetMesh()->GetAnimInstance());// 임시
			AnimInstance->bIsHoldingRifle = true; // 임시
		}


	}

	//Siren
	class AABItemSiren* Siren;
	Siren = Cast<AABItemSiren>(UGameplayStatics::GetActorOfClass(GetWorld(), AABItemSiren::StaticClass()));
	if (Siren)
	{
		Siren->OnInteract();
	}

	//FireExtinguisher
	class AWMAFireExtinguisher* FireExt;
	FireExt = Cast<AWMAFireExtinguisher>(UGameplayStatics::GetActorOfClass(GetWorld(), AWMAFireExtinguisher::StaticClass()));
	if (FireExt)
	{
		FireExt->OnInteract();
	}
}

void AWMACharacterPlayer::TakeItem(UABItemData* InItemData)
{
	ServerRPCTakeItem(InItemData);
}

float AWMACharacterPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (IsLocallyControlled())
	{
		if (!StartAttack1 && Stat->GetCurrentHp() < 20)
		{
			StartAttack1 = true;
			UpdateAttackedIMG();
			StartAttack1 = false;
		}
		if (!StartAttack2 && Stat->GetCurrentHp() < 15)
		{
			StartAttack2 = true;
			UpdateAttackedIMG();
			StartAttack2 = false;
		}
		if (!StartAttack3 && Stat->GetCurrentHp() < 10)
		{
			StartAttack3 = true;
			UpdateAttackedIMG();
			StartAttack3 = false;
		}
		//Stat->GetCurrentHp()
	}

	return DamageAmount;
}

void AWMACharacterPlayer::ServerRPCMovingSound_Implementation(FVector ClientLocation, bool bClientHolding, bool bClientCrouch)
{
	//MulticastRPCMovingSound();
	const float MinSoundThreshold = 50.0f; // 예시 임계값
	UE_LOG(LogTemp, Warning, TEXT("soundClient In"));

	if (!bClientHolding && !bClientCrouch) {
		UE_LOG(LogTemp, Warning, TEXT("dB 70"));
		const float SoundStrength = 40.0f;
		if (SoundStrength >= MinSoundThreshold) {
			AISenseHearing->ReportNoiseEvent(this, ClientLocation, SoundStrength, this, 20.0f, FName("WalkStep"));
		}
	}
	else {
		if (!bClientCrouch)
		{
			UE_LOG(LogTemp, Warning, TEXT("dB 120"));
			const float SoundStrength = 120.0f;
			if (SoundStrength >= MinSoundThreshold) {
				AISenseHearing->ReportNoiseEvent(this, ClientLocation, SoundStrength, this, 30.0f, FName("RunStep"));
			}
		}
	}
}

void AWMACharacterPlayer::MulticastRPCMovingSound_Implementation()
{
	const float MinSoundThreshold = 50.0f; // 예시 임계값

	if (!bIsHoldingSprintButton) {
		UE_LOG(LogTemp, Warning, TEXT("dB 70"));
		const float SoundStrength = 40.0f;
		if (SoundStrength >= MinSoundThreshold) {
			AISenseHearing->ReportNoiseEvent(this, GetActorLocation(), SoundStrength, this, 20.0f, FName("WalkStep"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("dB 120"));
		const float SoundStrength = 120.0f;
		if (SoundStrength >= MinSoundThreshold) {
			AISenseHearing->ReportNoiseEvent(this, GetActorLocation(), SoundStrength, this, 30.0f, FName("RunStep"));
		}
	}
}

void AWMACharacterPlayer::ServerRPCTakeItem_Implementation(UABItemData* InItemData)
{
	MulticastRPCTakeItem(InItemData);
}

void AWMACharacterPlayer::MulticastRPCTakeItem_Implementation(UABItemData* InItemData)
{
	if (InItemData) {
		TakeItemActions[(uint8)InItemData->Type].ItemDelegate.ExecuteIfBound(InItemData);
	}
}


