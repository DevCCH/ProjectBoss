// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Input/EPBAbilityInputId.h"
#include "PBGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPBGameplayAbility();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	FGameplayTag StartTag;

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EPBAbilityInputId AbilityInputID = EPBAbilityInputId::None;

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EPBAbilityInputId AbilityID = EPBAbilityInputId::None;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	TSubclassOf<class UGameplayEffect> SetAbilityTagGameplayEffect;

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "AddAbilityTag"))
	void K2_OnAddAbilityTag();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "RemoveAbilityTag"))

	void K2_OnRemoveAbilityTag();

	void AddAbilityTag();
	void RemoveAbilityTag();
};
