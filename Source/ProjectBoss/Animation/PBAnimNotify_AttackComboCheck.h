// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PBAnimNotify_AttackComboCheck.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBAnimNotify_AttackComboCheck : public UAnimNotify
{
	GENERATED_BODY()
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
