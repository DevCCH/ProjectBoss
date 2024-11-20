// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PBCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = "Character Movement: Run Movement", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	float RunSpeedMul;

	virtual float GetMaxSpeed()const override;

public:
	UPROPERTY()
	uint8 bIsRunning;

	UFUNCTION(BlueprintCallable)
	void StartSprint();
	UFUNCTION(BlueprintCallable)
	void StopSprint();
};
