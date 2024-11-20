// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PBAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	class UCharacterMovementComponent* Movement;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = "true"))
	uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreashould;

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeBeginPlay() override;
};
