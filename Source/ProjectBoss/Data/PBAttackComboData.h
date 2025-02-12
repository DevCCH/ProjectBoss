// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PBAttackComboData.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FAttackComboData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SectionName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AttackInputStartFrame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AttackInputEndFrame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> DamageEffect;
};

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBAttackComboData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AnimMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAttackComboData> ComboDataArray;
};