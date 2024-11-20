// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsClasses.h"
#include "PBAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;
};
