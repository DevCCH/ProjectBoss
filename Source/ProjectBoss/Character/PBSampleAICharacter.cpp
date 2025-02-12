// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PBSampleAICharacter.h"
#include "Ability/PBAbilitySystemComponent.h"


APBSampleAICharacter::APBSampleAICharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UPBAbilitySystemComponent>(TEXT("AbiliySystemComponent"));
}

void APBSampleAICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	UE_LOG(LogTemp, Log, TEXT("Possess"))
}
