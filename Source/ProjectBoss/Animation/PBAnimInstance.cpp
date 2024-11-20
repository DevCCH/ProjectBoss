// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PBAnimInstance.h"
#include "Character/PBCharacterBase.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPBAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Movement)
	{
		MoveSpeed = Movement->Velocity.Size2D();

		bIsFalling = Movement->IsFalling();

		bIsJumping = bIsFalling & (Movement->Velocity.Z > JumpingThreashould);
	}
}

void UPBAnimInstance::NativeBeginPlay()
{
	AActor* Actor = GetOwningActor();
	APBCharacterBase* CharBase = Cast<APBCharacterBase>(Actor);
	Movement = CharBase->GetCharacterMovement();
}
