// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/WMAAnimationCloseAttackInterface.h"
#include "Interface/WMAStepInterface.h"
#include "Interface/ABCharacterItemInterface.h"
#include "Item/ABWeaponItemData.h"
#include "Engine/StreamableManager.h"
#include "WMACharacterBase.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UABItemData* /*InItemData*/);
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper {

	GENERATED_BODY()
	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {}

	FOnTakeItemDelegate ItemDelegate;

};

UCLASS()
class WMA_API AWMACharacterBase : public ACharacter, public IWMAAnimationCloseAttackInterface, public IABCharacterItemInterface, public IWMAStepInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWMACharacterBase();

	virtual void PostInitializeComponents() override;

	virtual void SetCharacterControlData(const class UWMACharacterControlData* CharacterControlData);


//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 콤보 액션(애니메이션 몽타주) Combo Action Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWMAComboActionData> ComboActionData;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	virtual void NotifyComboActionEnd();
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;

// 근접 공격 Close Attack Hit Section
protected:
	virtual void CloseAttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// 죽는 모션 Dead Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> AttackedMontage;

	virtual void SetAttacked();
	void PlayAttackedAnimation();

	void EnableMovement();



public:
	int32 GetName();
	void SetName(int32 InNewName);																			// CharacterStatTable 에서 Name열 넣어 플레이어인지 NPC인지 알려주기

// Item Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> ShortWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> DisposableWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> LongWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> ThrowItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Gun;

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions;

	virtual void TakeItem(class UABItemData* InItemData) override;
	virtual void EquipShort(class UABItemData* InItemData);
	virtual void EquipDisposable(class UABItemData* InItemData);
	virtual void EquipLong(class UABItemData* InItemData);
	virtual void EquipThrow(class UABItemData* InitemData);
	virtual void EquipGun(class UABItemData* InitemData);
	
	UPROPERTY(VisibleAnywhere, Category = Equipment)
	EItemType WeaponNow;			// 어떤 무기를 들고 있는지 확인

public:
	void MeshLoadCompleted();

	TSharedPtr<FStreamableHandle> MeshHandle;

// Stat Section
protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWMACharacterStatComponent> Stat;

protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> FAUW1;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> FAUW2;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> FAUW3;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "UI")
	TSubclassOf<UUserWidget> IMGWidgetClass;

	//UPROPERTY()
	//UUserWidget* FirstAttackedWidget;
	TSubclassOf<UUserWidget> FirstAttackedWidgetClass;
	TSubclassOf<UUserWidget> SecondAttackedWidgetClass;
	TSubclassOf<UUserWidget> ThirdAttackedWidgetClass;

public:

	void UpdateAttackedIMG() const;

	UINT8 StartAttack1 = 0;
	UINT8 StartAttack2 = 0;
	UINT8 StartAttack3 = 0;

protected:
	virtual void StepCheck() override;
};

