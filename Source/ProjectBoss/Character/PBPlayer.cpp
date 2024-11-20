// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PBPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemComponent.h"
#include "Player/PBPlayerState.h"
#include "Ability/PBAbilitySystemComponent.h"
#include "Input/EPBAbilityInputId.h"
#include "Attribute/PBCharacterAttributeSetBase.h"
#include "Player/PBPlayerController.h"

APBPlayer::APBPlayer()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

void APBPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APBPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// BindASCInput();
}

void APBPlayer::OnRep_PlayerState()
{
	UE_LOG(LogTemp, Log, TEXT("PBPlayer::OnRep_PlayerState"));
	APBPlayerController* PC = Cast<APBPlayerController>(GetController());
	PC->CreateHUD();
}

void APBPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APBPlayerState* PS = Cast<APBPlayerState>(GetPlayerState());
	if (PS)
	{
		AbilitySystemComponent = Cast<UPBAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		AttributeSetBase = PS->GetAttributeSet();

		AddCharacterAbilities();

		InitAttributes();

		ApplyStartupGameplayEffects();

		APBPlayerController* PC = Cast<APBPlayerController>(GetController());
		PC->CreateHUD();

		UE_LOG(LogTemp, Log, TEXT("MaxHP : %f, HP : %f"), AttributeSetBase->GetMaxHP(), AttributeSetBase->GetHP());
	}
}

void APBPlayer::Look(FVector2D LooKVector)
{
	AddControllerYawInput(LooKVector.X);
	AddControllerPitchInput(LooKVector.Y);
}

float APBPlayer::GetStamina()
{
	return AttributeSetBase->GetStamina();
}

void APBPlayer::PrintAllTag()
{
	FGameplayTagContainer Container;

	/*auto Context = AbilitySystemComponent->MakeEffectContext();
	Context.AddSourceObject(this);

	auto SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(TestEffect, 1, Context);

	auto Handle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	if (Handle.WasSuccessfullyApplied())
	{
		UE_LOG(LogTemp, Log, TEXT("S"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("F"));
	}

	if (Handle.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("V"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("I"));
	}

	auto ASC = Handle.GetOwningAbilitySystemComponent();
	if (ASC)
	{
		ASC->GetOwnedGameplayTags(Container);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ASC is Null!!"));
		return;
	}*/

	AbilitySystemComponent->GetOwnedGameplayTags(Container);

	auto TagArray = Container.GetGameplayTagArray();

	UE_LOG(LogTemp, Log, TEXT("PrintAllTags. TagCounts : %d"), TagArray.Num());

	for (auto Tag : TagArray)
	{
		FString NameStr = Tag.GetTagName().ToString();
		UE_LOG(LogTemp, Log, TEXT("TagName : %s"), *NameStr);
	}
}
