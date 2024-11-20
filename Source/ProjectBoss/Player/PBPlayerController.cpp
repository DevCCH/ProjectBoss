// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PBPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Character/PBPlayer.h"
#include "AbilitySystemComponent.h"
#include "Input/PBInputComponent.h"
#include "Player/PBPlayerState.h"
#include "Ability/PBAbilitySystemComponent.h"
#include "PBHudWidget.h"
#include "Attribute/PBCharacterAttributeSetBase.h"

APBPlayerController::APBPlayerController()
{

}

void APBPlayerController::CreateHUD()
{
	if (HudWidget)
		return;

	if (!IsLocalPlayerController())
		return;

	APBPlayerState* PS = GetPlayerState<APBPlayerState>();
	if (!PS)
		return;

	UPBCharacterAttributeSetBase* AttributeSet = PS->GetAttributeSet();

	HudWidget = CreateWidget<UPBHudWidget>(this, HudWidgetClass);
	HudWidget->AddToViewport();

	HudWidget->OnMaxHPChanged(AttributeSet->GetMaxHP());
	HudWidget->OnHPChanged(AttributeSet->GetHP());
	HudWidget->OnHPRegenChanged(AttributeSet->GetHPRegen());
	HudWidget->OnMaxStaminaChanged(AttributeSet->GetMaxStamina());
	HudWidget->OnStaminaChanged(AttributeSet->GetStamina());
	HudWidget->OnStaminaRegenChanged(AttributeSet->GetStaminaRegen());

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHPAttribute()).AddUObject(this, &APBPlayerController::OnMaxHPValueChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHPAttribute()).AddUObject(this, &APBPlayerController::OnHPValueChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHPRegenAttribute()).AddUObject(this, &APBPlayerController::OnHPRegenValueChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &APBPlayerController::OnMaxStaminaValueChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddUObject(this, &APBPlayerController::OnStaminaValueChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaRegenAttribute()).AddUObject(this, &APBPlayerController::OnStaminaRegenValueChanged);

	UE_LOG(LogTemp, Log, TEXT("Succedded"));
}

void APBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APBPlayer>(GetCharacter());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void APBPlayerController::SetupInputComponent()
{
	UE_LOG(LogTemp, Log, TEXT("PC_SetupInputComponent"));
	Super::SetupInputComponent();

	UPBInputComponent* PBInputComponent = CastChecked<UPBInputComponent>(InputComponent);

	int a = 10;

	PBInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APBPlayerController::MoveInput);
	PBInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APBPlayerController::LookInput);
	PBInputComponent->BindAbilityActions(InputDataAsset, this, &APBPlayerController::AbilityInputTagPressed, &APBPlayerController::AbilityInputTagReleased, &APBPlayerController::AbilityInputTagHeld);


	auto PBState = GetPlayerState<APBPlayerState>();
	AbilitySystemComponent = Cast<UPBAbilitySystemComponent>(PBState->GetAbilitySystemComponent());
}

void APBPlayerController::OnRep_PlayerState()
{

}

void APBPlayerController::LookInput(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	PlayerCharacter->Look(LookVector);
}

void APBPlayerController::MoveInput(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	PlayerCharacter->Move(MoveVector);
}

void APBPlayerController::OnMaxHPValueChanged(const FOnAttributeChangeData& Data)
{
	HudWidget->OnMaxHPChanged(Data.NewValue);
}

void APBPlayerController::OnHPValueChanged(const FOnAttributeChangeData& Data)
{
	HudWidget->OnHPChanged(Data.NewValue);
}

void APBPlayerController::OnHPRegenValueChanged(const FOnAttributeChangeData& Data)
{
	HudWidget->OnHPRegenChanged(Data.NewValue);
}

void APBPlayerController::OnMaxStaminaValueChanged(const FOnAttributeChangeData& Data)
{
	HudWidget->OnMaxStaminaChanged(Data.NewValue);
}

void APBPlayerController::OnStaminaValueChanged(const FOnAttributeChangeData& Data)
{
	HudWidget->OnStaminaChanged(Data.NewValue);
}

void APBPlayerController::OnStaminaRegenValueChanged(const FOnAttributeChangeData& Data)
{
	HudWidget->OnStaminaRegenChanged(Data.NewValue);
}

void APBPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagPressed(InputTag);
}

void APBPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagReleased(InputTag);
}

void APBPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagHeld(InputTag);
}