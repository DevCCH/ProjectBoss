// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/PBCharacterAttributeSetBase.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UPBCharacterAttributeSetBase::UPBCharacterAttributeSetBase()
{
}

void UPBCharacterAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetMaxHPAttribute())
	{
		AdjustAttributeForMaxChange(HP, MaxHP, NewValue, GetHPAttribute());
	}
	else if (Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
	}
}

void UPBCharacterAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHPAttribute())
	{
		SetHP(FMath::Clamp(GetHP(), 0, GetMaxHP()));
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::ClampAngle(GetStamina(), 0, GetMaxStamina()));
	}
}

void UPBCharacterAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UPBCharacterAttributeSetBase::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP)
{
}

void UPBCharacterAttributeSetBase::OnRep_HP(const FGameplayAttributeData& OldHP)
{
}

void UPBCharacterAttributeSetBase::OnRep_HPRegen(const FGameplayAttributeData& OldHPRegen)
{
}

void UPBCharacterAttributeSetBase::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
}

void UPBCharacterAttributeSetBase::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
}

void UPBCharacterAttributeSetBase::OnRep_StaminaRegen(const FGameplayAttributeData& OldStaminaRegen)
{
}

void UPBCharacterAttributeSetBase::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UPBAbilitySystemComponent* AbilitySystemComponent = Cast<UPBAbilitySystemComponent>(GetOwningAbilitySystemComponent());

	const float CurMaxValue = MaxAttribute.GetCurrentValue();
	if (AbilitySystemComponent && !FMath::IsNearlyEqual(CurMaxValue, NewMaxValue))
	{
		const float CurValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurMaxValue > 0.f) ? (NewMaxValue / CurMaxValue * CurValue) - CurValue : NewMaxValue;

		AbilitySystemComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}