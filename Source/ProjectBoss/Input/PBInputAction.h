// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsClasses.h"
#include "PBInputAction.generated.h"

class UInputAction;

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct PROJECTBOSS_API FPBInputAction
{
	GENERATED_USTRUCT_BODY()
public:
	FPBInputAction();
	~FPBInputAction();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 bIsPressed : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 bIsReleased : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 bIsHeld : 1;
};