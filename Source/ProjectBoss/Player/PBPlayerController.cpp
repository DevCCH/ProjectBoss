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
	if (!IsLocalPlayerController())
		return;

	if (HudWidget)
		return;

	APBPlayerState* PS = GetPlayerState<APBPlayerState>();
	if (PS)
	{
		UPBCharacterAttributeSetBase* AttributeSet = PS->GetAttributeSet();

		HudWidget = CreateWidget<UPBHudWidget>(this, HudWidgetClass);
		HudWidget->AddToViewport();

		FString LogStr = FString::Printf(TEXT("MaxHP : %f"), AttributeSet->GetMaxHP());
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, *LogStr);

		HudWidget->OnMaxHPChanged(AttributeSet->GetMaxHP());
		HudWidget->OnHPChanged(AttributeSet->GetHP());
		HudWidget->OnHPRegenChanged(AttributeSet->GetHPRegen());
		HudWidget->OnMaxStaminaChanged(AttributeSet->GetMaxStamina());
		HudWidget->OnStaminaChanged(AttributeSet->GetStamina());
		HudWidget->OnStaminaRegenChanged(AttributeSet->GetStaminaRegen());

		auto ASC = PS->GetAbilitySystemComponent();

		if (ASC)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHPAttribute()).AddUObject(this, &APBPlayerController::OnMaxHPValueChanged);
			ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHPAttribute()).AddUObject(this, &APBPlayerController::OnHPValueChanged);
			ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHPRegenAttribute()).AddUObject(this, &APBPlayerController::OnHPRegenValueChanged);
			ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &APBPlayerController::OnMaxStaminaValueChanged);
			ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddUObject(this, &APBPlayerController::OnStaminaValueChanged);
			ASC->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaRegenAttribute()).AddUObject(this, &APBPlayerController::OnStaminaRegenValueChanged);
		}
	}
}

FRotator APBPlayerController::GetRotatorFromLastMoveInput()
{
	FRotator rotator;

	if (LastMoveInputVector.X + LastMoveInputVector.Y != 0)
	{
		// 입력 벡터를 노멀라이즈
		FVector MovementDirection = FVector(LastMoveInputVector.X, LastMoveInputVector.Y, 0.0f).GetSafeNormal();

		// 월드 기준으로 이동 방향 변환 (로컬 기준 → 월드 기준)
		FRotator controlRotation = GetControlRotation();
		auto Euler = controlRotation.Euler();
		Euler.Y = 0;
		controlRotation = controlRotation.MakeFromEuler(Euler);
		FVector WorldDirection = FRotationMatrix(controlRotation).TransformVector(MovementDirection);

		// 목표 회전 계산
		rotator = WorldDirection.Rotation();
	}
	else
	{
		APawn* pawn = GetPawn();
		if (pawn)
		{
			rotator = pawn->GetActorRotation();
		}
	}
	return rotator;
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
	Super::SetupInputComponent();

	UPBInputComponent* PBInputComponent = CastChecked<UPBInputComponent>(InputComponent);

	PBInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APBPlayerController::MoveInput);
	PBInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APBPlayerController::MoveInputCompleted);
	PBInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APBPlayerController::LookInput);
	PBInputComponent->BindAbilityActions(InputDataAsset, this, &APBPlayerController::AbilityInputTagPressed, &APBPlayerController::AbilityInputTagReleased, &APBPlayerController::AbilityInputTagHeld);
}

void APBPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	auto PBState = GetPlayerState<APBPlayerState>();
	AbilitySystemComponent = Cast<UPBAbilitySystemComponent>(PBState->GetAbilitySystemComponent());

	CreateHUD();
}

void APBPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	auto PBState = GetPlayerState<APBPlayerState>();
	AbilitySystemComponent = Cast<UPBAbilitySystemComponent>(PBState->GetAbilitySystemComponent());
}

void APBPlayerController::LookInput(const FInputActionValue& Value)
{
	if (!IsLocalPlayerController())
		return;

	FVector2D LookVector = Value.Get<FVector2D>();

	PlayerCharacter->Look(LookVector);
}

void APBPlayerController::MoveInput(const FInputActionValue& Value)
{
	if (!IsLocalPlayerController())
		return;

	FVector2D MoveVector = Value.Get<FVector2D>();

	LastMoveInputVector = MoveVector;

	PlayerCharacter->Move(MoveVector);
}

void APBPlayerController::MoveInputCompleted(const FInputActionValue& Value)
{
	if (!IsLocalPlayerController())
		return;

	LastMoveInputVector = FVector2D::ZeroVector;
}

void APBPlayerController::DodgeInput(const FInputActionValue& Value)
{
	if (!IsLocalPlayerController())
		return;

	PlayerCharacter->Dodge();
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