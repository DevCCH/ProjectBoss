// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PBCharacterBase.h"
#include "PBSampleAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API APBSampleAICharacter : public APBCharacterBase
{
	GENERATED_BODY()
	
public:
	APBSampleAICharacter();

protected:
	virtual void PossessedBy(AController* NewController) override;
};
