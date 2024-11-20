// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "GameplayTagsClasses.h"
#include "GameplayEffectTypes.h"
#include "PBPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class APBPlayer;
class UPBASCInputDataAsset;
class UPBHudWidget;

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API APBPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APBPlayerController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UPBASCInputDataAsset> InputDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UPBHudWidget> HudWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<UPBHudWidget> HudWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	APBPlayer* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag GameplayTag;

	class UPBAbilitySystemComponent* AbilitySystemComponent;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	virtual void OnRep_PlayerState() override;

protected:
	void LookInput(const FInputActionValue& Value);
	void MoveInput(const FInputActionValue& Value);

	// Widget Section
	void OnMaxHPValueChanged(const FOnAttributeChangeData& Data);
	void OnHPValueChanged(const FOnAttributeChangeData& Data);
	void OnHPRegenValueChanged(const FOnAttributeChangeData& Data);
	void OnMaxStaminaValueChanged(const FOnAttributeChangeData& Data);
	void OnStaminaValueChanged(const FOnAttributeChangeData& Data);
	void OnStaminaRegenValueChanged(const FOnAttributeChangeData& Data);

public:
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	void CreateHUD();
};