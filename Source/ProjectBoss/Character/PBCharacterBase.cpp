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
#include "GameplayEffect.h"
#include "Components/CapsuleComponent.h"
#include "Data/PBAttackComboData.h"
#include "Animation/AnimMontage.h"
#include "Player/PBPlayerController.h"

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

void APBCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	auto MeshComp = GetMesh();
	if (MeshComp)
	{
		AnimInstance = MeshComp->GetAnimInstance();
		UE_LOG(LogTemp, Log, TEXT("Bind OnMontageEnded"));
		if (AnimInstance)
			AnimInstance->OnMontageEnded.AddDynamic(this, &APBCharacterBase::AttackEnd);
	}
}

void APBCharacterBase::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ENetRole::ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("AddCharacterAbilities return"));

		return;
	}

	for (TSubclassOf<UPBGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbility, 1);
		AbilitySpec.SourceObject = this;

		if (const UPBGameplayAbility* PBAbility = Cast<UPBGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(PBAbility->StartTag);

			FString NameStr = FString::Printf(TEXT("GivenAbility : %s"), *PBAbility->StartTag.GetTagName().ToString());

			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, *NameStr);

			auto Handle = AbilitySystemComponent->GiveAbility(AbilitySpec);
			if (Handle.IsValid())
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Give Suc"));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Give Fail"));
			}
		}

		/*AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));*/
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = true;
}

void APBCharacterBase::InitAttributes()
{
	if (IsLocallyControlled())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Call InitAtt"));
	}

	if (AbilitySystemComponent == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("InitAtt return 0"));
		return;
	}

	if (DefaultAttributes == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("InitAtt return 1"));
		return;
	}

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, ContextHandle);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
	}
}

void APBCharacterBase::ApplyStartupGameplayEffects()
{
	if (GetLocalRole() != ENetRole::ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bStartupEffectsApplied)
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

void APBCharacterBase::AttackEnd(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Log, TEXT("End"))
		bNowAttacking = false;
	CurComboIndex = 0;
	bCanPreInput = false;
}

void APBCharacterBase::CheckAttackCombo()
{
	if (CurComboIndex >= AttackComboData->ComboDataArray.Num())
	{
		return;
	}

	if (bIsReservedNextCombo)
	{
		auto PlayerController = Cast<APBPlayerController>(GetController());
		if (PlayerController)
		{
			FRotator rotator = PlayerController->GetRotatorFromLastMoveInput();
			SetActorRotation(rotator);
		}

		CurComboIndex++;
		auto ComboData = AttackComboData->ComboDataArray[CurComboIndex];

		AnimInstance->Montage_JumpToSection(ComboData.SectionName, AttackComboData->AnimMontage);

		bCanPreInput = false;

		bIsReservedNextCombo = false;
	}
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
	MovementCom->bIsDodging = true;
}

UAbilitySystemComponent* APBCharacterBase::GetAbilitySystemComponent() const
{
	if (AbilitySystemComponent)
		return AbilitySystemComponent;

	APBPlayerState* PBPlayerState = Cast<APBPlayerState>(GetPlayerState());
	return PBPlayerState->GetAbilitySystemComponent();
}

void APBCharacterBase::AttackHitCheck()
{
	TArray<FHitResult> OutHitResultArr;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackRange = 40.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 30.0f;

	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	bool HitDetected = GetWorld()->SweepMultiByChannel(OutHitResultArr, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AttackRadius), Params);
	if (HitDetected)
	{
		TSet<AActor*> AlreadyHittedActorSet;

		for (int i = 0; i < OutHitResultArr.Num(); i++)
		{
			auto hitResult = OutHitResultArr[i];

			auto Actor = hitResult.GetActor();

			if (AlreadyHittedActorSet.Contains(Actor))
				continue;

			auto Character = Cast<APBCharacterBase>(Actor);
			if (Character == nullptr)
				continue;

			auto ASC = Character->AbilitySystemComponent;
			if (ASC)
			{
				auto CurComboData = GetCurAttackComboData();
			
				auto context = ASC->MakeEffectContext();
				auto DamageEffect = CurComboData.DamageEffect;
				context.AddInstigator(ASC->GetAvatarActor(), ASC->GetAvatarActor());
				FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(CurComboData.DamageEffect, 1, context);
				if (SpecHandle.IsValid())
				{
					ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				}

				AlreadyHittedActorSet.Add(Actor);
				// AbilitySystemComponent->ApplyGameplayEffectToTarget((UGameplayEffect*)DamageEffect.Get(), ASC);
				// AbilitySystemComponent->ApplyGameplayEffectToTarget()
			}
		}
	}

#if ENABLE_DRAW_DEBUG
	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 1.0f);
#endif
}

void APBCharacterBase::DodgeTriggered()
{
	UE_LOG(LogTemp, Log, TEXT("DodgeStart"))
}

void APBCharacterBase::DodgeEndTriggered()
{
	MovementCom->bIsDodging = false;
	UE_LOG(LogTemp, Log, TEXT("DodgeEnd"))
}

FAttackComboData APBCharacterBase::GetCurAttackComboData() const
{
 	auto data = AttackComboData->ComboDataArray[CurComboIndex];

	return data;
}

// Called every frame
void APBCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

bool APBCharacterBase::AttackInput()
{
	if (!bNowAttacking)
	{
		AttackStart();
		return true;
	}
	else
	{
		if (!bCanPreInput)
			return false;

		if (bIsReservedNextCombo)
			return false;

		if (CurComboIndex < AttackComboData->ComboDataArray.Num())
		{
			/*auto Data = AttackComboData->ComboDataArray[CurComboIndex];
			AnimInstance->Montage_*/
			bIsReservedNextCombo = true;
			return true;
		}
		else
		{
			return false;
		}
	}
}

void APBCharacterBase::SetPreInputEnable()
{
	bCanPreInput = true;
}

void APBCharacterBase::AttackStart()
{
	if (bNowAttacking)
		return;

	bNowAttacking = true;

	bIsReservedNextCombo = false;

	CurComboIndex = 0;

	auto PlayerController = Cast<APBPlayerController>(GetController());
	if (PlayerController)
	{
		FRotator rotator = PlayerController->GetRotatorFromLastMoveInput();
		SetActorRotation(rotator);
	}

	AnimInstance->Montage_Play(AttackComboData->AnimMontage);
}