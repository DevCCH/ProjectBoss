// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AbilitySystemInterface.h"
#include "Interface/PBAnimationAttackable.h"
#include "Interface/PBAnimationDodgable.h"
#include "PBCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPBCharacterMovementComponent;
class UPBGameplayAbility;
class UGameplayEffect;
class UPBAbilitySystemComponent;
class UPBAttackComboData;
class UAnimMontage;
class UAnimInstance;

UCLASS()
class PROJECTBOSS_API APBCharacterBase : public ACharacter, public IAbilitySystemInterface, public IPBAnimationAttackable, public IPBAnimationDodgable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APBCharacterBase();

protected:
	UPBCharacterMovementComponent* MovementCom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxRunningSpeed;
	float DefaultSpeed;

	TObjectPtr<UPBAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<class UPBCharacterAttributeSetBase> AttributeSetBase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UPBGameplayAbility>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UPBAttackComboData> AttackComboData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	uint8 bNowAttacking : 1;

	TObjectPtr<UAnimInstance> AnimInstance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	uint8 bCanPreInput : 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	uint8 bIsReservedNextCombo : 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int CurComboIndex;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class APBWeapon> Weapon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float AttackSpeed = 1.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void AddCharacterAbilities();

	virtual void InitAttributes();

	virtual void ApplyStartupGameplayEffects();

	UFUNCTION(BlueprintCallable)
	void AttackEnd(UAnimMontage* Montage, bool bInterrupted);
	void AttackStart();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool AttackInput();

	UFUNCTION(BlueprintCallable)
	void SetPreInputEnable();

	UFUNCTION(BlueprintCallable)
	void CheckAttackCombo();

	void Move(FVector2D MoveDirVector);
	void Run();
	void StopRun();
	void Dodge();

	// IAbilitySystemInterface을(를) 통해 상속됨
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void AttackHitCheck() override;
	virtual void DodgeTriggered() override;
	virtual void DodgeEndTriggered() override;

	UFUNCTION(BlueprintCallable)
	FAttackComboData GetCurAttackComboData() const;
};