// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AbilitySystemInterface.h"
#include "PBCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPBCharacterMovementComponent;
class UPBGameplayAbility;
class UGameplayEffect;
class UPBAbilitySystemComponent;

UCLASS()
class PROJECTBOSS_API APBCharacterBase : public ACharacter, public IAbilitySystemInterface
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UPBGameplayAbility>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AddCharacterAbilities();

	virtual void InitAttributes();

	virtual void ApplyStartupGameplayEffects();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// IAbilitySystemInterface을(를) 통해 상속됨
	

	void Move(FVector2D MoveDirVector);
	void Run();
	void StopRun();
	void Dodge();

	// IAbilitySystemInterface을(를) 통해 상속됨
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
