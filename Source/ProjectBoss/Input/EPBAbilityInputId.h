// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPBAbilityInputId : uint8
{
	None		UMETA(DisplayName = "None"),
	Confirm		UMETA(DisplayName = "Confirm"),
	Cancel		UMETA(DisplayName = "Cancle"),
	Attack1		UMETA(DisplayName = "Attack1"),
	Attack2		UMETA(DisplayName = "Attack2"),
	Sprint		UMETA(DisplayName = "Sprint"),
	Jump		UMETA(DisplayName = "Jump"),
};