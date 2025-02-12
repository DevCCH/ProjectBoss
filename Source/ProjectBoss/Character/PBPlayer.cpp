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
#include "Animation/AnimMontage.h"
#include "Weapon/PBWeapon.h"

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

	FActorSpawnParameters SpawnParam;
	UClass* Casted = Cast<UClass>(Weapon);
	auto SpanwedWeapon = GetWorld()->SpawnActor<APBWeapon>(Casted, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);
	FName WeaponSocketName(TEXT("WeaponSocket"));
	if (SpanwedWeapon)
	{
		SpanwedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
	}
}

void APBPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APBPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	APBPlayerState* PS = GetPlayerState<APBPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UPBAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		AttributeSetBase = PS->GetAttributeSet();

		AddCharacterAbilities();

		InitAttributes();

		ApplyStartupGameplayEffects();

		APBPlayerController* PC = Cast<APBPlayerController>(PS->GetPlayerController());
		if (PC)
		{
			PC->CreateHUD();
		}
	}
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
		if (PC)
			PC->CreateHUD();
	}
}

void APBPlayer::Look(FVector2D LooKVector)
{
	AddControllerYawInput(LooKVector.X);
	if (!bIsLockVerticalLook)
		AddControllerPitchInput(LooKVector.Y);
}

void APBPlayer::Dodge()
{

}

float APBPlayer::GetStamina()
{
	return AttributeSetBase->GetStamina();
}

void APBPlayer::PrintAllTag()
{
	FGameplayTagContainer Container;
	AbilitySystemComponent->GetOwnedGameplayTags(Container);

	auto TagArray = Container.GetGameplayTagArray();

	UE_LOG(LogTemp, Log, TEXT("PrintAllTags. TagCounts : %d"), TagArray.Num());

	for (auto Tag : TagArray)
	{
		FString NameStr = Tag.GetTagName().ToString();
		UE_LOG(LogTemp, Log, TEXT("TagName : %s"), *NameStr);
	}
}
