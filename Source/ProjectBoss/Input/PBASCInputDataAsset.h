// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PBInputAction.h"
#include "PBASCInputDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBASCInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FPBInputAction> AbilityInputActionArray;
};
