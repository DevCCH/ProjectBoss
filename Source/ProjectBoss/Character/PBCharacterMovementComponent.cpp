// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PBCharacterMovementComponent.h"

float UPBCharacterMovementComponent::GetMaxSpeed() const
{
	switch (MovementMode)
	{
	case MOVE_Walking:
	case MOVE_NavWalking:
	{
		float Speed = IsCrouching() ? MaxWalkSpeedCrouched : MaxWalkSpeed;
		if (bIsRunning)
			Speed *= RunSpeedMul;
		return Speed;
	}
	case MOVE_Falling:
		return MaxWalkSpeed;
	case MOVE_Swimming:
		return MaxSwimSpeed;
	case MOVE_Flying:
		return MaxFlySpeed;
	case MOVE_Custom:
		return MaxCustomMovementSpeed;
	case MOVE_None:
	default:
		return 0.f;
	}
}

void UPBCharacterMovementComponent::StartSprint()
{
	bIsRunning = true;
}

void UPBCharacterMovementComponent::StopSprint()
{
	bIsRunning = false;
}
