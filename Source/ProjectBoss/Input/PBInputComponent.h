// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "PBInputAction.h"
#include "PBASCInputDataAsset.h"
#include "PBInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOSS_API UPBInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UPBASCInputDataAsset* InputDataAsset , UserClass* Object, PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template<typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
inline void UPBInputComponent::BindAbilityActions(const UPBASCInputDataAsset* InputDataAsset, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	for (const FPBInputAction& Action : InputDataAsset->AbilityInputActionArray)
	{
		
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc && Action.bIsPressed)
			{
				UE_LOG(LogTemp, Log, TEXT("Pressed Binded"));
				UE_LOG(LogTemp, Log, TEXT("Tag Name : %s"), *Action.InputTag.GetTagName().ToString());
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc && Action.bIsReleased)
			{
				UE_LOG(LogTemp, Log, TEXT("Released Binded"));
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}

			if (HeldFunc && Action.bIsHeld)
			{
				UE_LOG(LogTemp, Log, TEXT("Held Binded"));
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
