// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Ability/PBAbilitySystemComponent.h"
#include "PBCharacterAttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBCharacterAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPBCharacterAttributeSetBase();

	// AttributeSet Overrides
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_MaxHP)
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UPBCharacterAttributeSetBase, MaxHP);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_HP)
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UPBCharacterAttributeSetBase, HP);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HP", ReplicatedUsing = OnRep_HP)
	FGameplayAttributeData HPRegen;
	ATTRIBUTE_ACCESSORS(UPBCharacterAttributeSetBase, HPRegen);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UPBCharacterAttributeSetBase, MaxStamina);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UPBCharacterAttributeSetBase, Stamina);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData StaminaRegen;
	ATTRIBUTE_ACCESSORS(UPBCharacterAttributeSetBase, StaminaRegen);

	UFUNCTION()
	virtual void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP);
	UFUNCTION()
	virtual void OnRep_HP(const FGameplayAttributeData& OldHP);
	UFUNCTION()
	virtual void OnRep_HPRegen(const FGameplayAttributeData& OldHPRegen);
	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);
	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	UFUNCTION()
	virtual void OnRep_StaminaRegen(const FGameplayAttributeData& OldStaminaRegen);

protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
