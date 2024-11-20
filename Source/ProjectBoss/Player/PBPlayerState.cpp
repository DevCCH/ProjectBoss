// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PBPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Input/PBInputComponent.h"
#include "Input/EPBAbilityInputId.h"
#include "Ability/PBAbilitySystemComponent.h"
#include "Attribute/PBCharacterAttributeSetBase.h"

APBPlayerState::APBPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UPBAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UPBCharacterAttributeSetBase>(TEXT("AttributeSetBase"));
}

UAbilitySystemComponent* APBPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UPBCharacterAttributeSetBase* APBPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

void APBPlayerState::BindASC()
{
	if (!IsBinded && AbilitySystemComponent && IsValid(InputComponent))
	{
		UE_LOG(LogTemp, Log, TEXT("Binded"));
		FTopLevelAssetPath AbilityEnumAssetPath = FTopLevelAssetPath(FName("/Script/ProjectBoss"), FName("EPBAbilityInputId"));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), AbilityEnumAssetPath, static_cast<int32>(EPBAbilityInputId::Confirm), static_cast<int32>(EPBAbilityInputId::Cancel)));

		IsBinded = true;
	}
}
