// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "PBPlayerState.generated.h"

class UPBCharacterAttributeSetBase;

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API APBPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	APBPlayerState();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	class UPBAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	FGameplayTagContainer GameplayTagContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	TObjectPtr<UPBCharacterAttributeSetBase> AttributeSet;

	bool IsBinded = false;

public:
	// IAbilitySystemInterface을(를) 통해 상속됨
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPBCharacterAttributeSetBase* GetAttributeSet() const;

	void BindASC();
};
