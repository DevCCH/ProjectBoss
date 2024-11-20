// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PBCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/PBCharacterMovementComponent.h"
#include "Ability/PBAbilitySystemComponent.h"
#include "Player/PBPlayerState.h"
#include "Ability/PBGameplayAbility.h"
#include "Attribute/PBCharacterAttributeSetBase.h"

// Sets default values
APBCharacterBase::APBCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APBCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	MovementCom = Cast<UPBCharacterMovementComponent>(GetCharacterMovement());
}

void APBCharacterBase::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UPBGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbility, 1);

		if (const UPBGameplayAbility* PBAbility = Cast<UPBGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(PBAbility->StartTag);

			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}

		/*AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));*/
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = true;
}

void APBCharacterBase::InitAttributes()
{
	if (AbilitySystemComponent == nullptr)
	{
		return;
	}

	if (DefaultAttributes == nullptr)
	{
		return;
	}

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, ContextHandle);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

void APBCharacterBase::ApplyStartupGameplayEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bStartupEffectsApplied)
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (auto effect : StartupEffects)
	{
		UE_LOG(LogTemp, Log, TEXT("TryApplyEffect"));
		FGameplayEffectSpecHandle Handle = AbilitySystemComponent->MakeOutgoingSpec(effect, 1, EffectContext);
		if (Handle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Handle.Data.Get());
			UE_LOG(LogTemp, Log, TEXT("Applied"));
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void APBCharacterBase::Move(FVector2D MoveDirVector)
{
	UPawnMovementComponent* Movement = GetMovementComponent();

	const FRotator Rotation = Controller->GetControlRotation();
	
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MoveDirVector.X);
	AddMovementInput(RightDirection, MoveDirVector.Y);
}

void APBCharacterBase::Run()
{
	if (MovementCom)
		MovementCom->StartSprint();
}

void APBCharacterBase::StopRun()
{
	if (MovementCom)
		MovementCom->StopSprint();
}

void APBCharacterBase::Dodge()
{
	
}

UAbilitySystemComponent* APBCharacterBase::GetAbilitySystemComponent() const
{
	if (AbilitySystemComponent)
		return AbilitySystemComponent;

	APBPlayerState* PBPlayerState = Cast<APBPlayerState>(GetPlayerState());
	return PBPlayerState->GetAbilitySystemComponent();
}

// Called every frame
void APBCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}