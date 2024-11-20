// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBHudWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	TObjectPtr<UProgressBar> HPBar;
	TObjectPtr<UProgressBar> StaminaBar;
	TObjectPtr<UTextBlock> HPTextBlock;
	TObjectPtr<UTextBlock> HPRegenTextBlock;
	TObjectPtr<UTextBlock> StaminaTextBlock;
	TObjectPtr<UTextBlock> StaminaRegenTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	float HPRegen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status)
	float StaminaRegen;

protected:
	virtual void NativeConstruct() override;

	void UpdateHPWidget();

	void UpdateStaminaWidget();

public:
	UFUNCTION(BlueprintCallable)
	void OnMaxHPChanged(float ChangedValue);

	UFUNCTION(BlueprintCallable)
	void OnHPChanged(float ChangedValue);

	UFUNCTION(BlueprintCallable)
	void OnHPRegenChanged(float ChangedValue);

	UFUNCTION(BlueprintCallable)
	void OnMaxStaminaChanged(float ChangedValue);

	UFUNCTION(BlueprintCallable)
	void OnStaminaChanged(float ChangedValue);

	UFUNCTION(BlueprintCallable)
	void OnStaminaRegenChanged(float ChangedValue);
};
