// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PBCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitiesClasses.h"
#include "GameplayTagsClasses.h"
#include "GameplayEffect.h"
#include "PBPlayer.generated.h"

class UInputAction;
class UInputMappingContext;
class UAbilitySystemComponent;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API APBPlayer : public APBCharacterBase
{
	GENERATED_BODY()
public:
	APBPlayer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))

	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))

	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FGameplayTag SprintTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> TestEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 bIsLockVerticalLook : 1;

	bool ASCInputBound = false;
protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void OnRep_PlayerState() override;

	virtual void PossessedBy(AController* NewController) override;

public:
	void Look(FVector2D LooKVector);

	void Dodge();

	UFUNCTION(BlueprintCallable)
	float GetStamina();

	UFUNCTION(BlueprintCallable)
	void PrintAllTag();
};
