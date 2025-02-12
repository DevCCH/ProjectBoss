// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PBBasicAIController.generated.h"

#define BBKEY_HOMEPOS TEXT("HomePos")
#define BBKEY_PATROLPOS TEXT("PatrolPos")
#define BBKEY_TARGET TEXT("Target")

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API APBBasicAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	APBBasicAIController();

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBehaviorTree> BTAsset;
};
