// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	USkeletalMeshComponent* TMesh = GetMesh();

	FVector Location = FVector(0.f, 0.f, -90.f);
	FRotator Rotator = FRotator(0.f, -90.f, 0.f);

	TMesh->SetRelativeLocationAndRotation(Location, Rotator);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));


	SetRootComponent(GetCapsuleComponent());
	
	GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);
	GetCapsuleComponent()->SetCapsuleRadius(20.0f);
	SpringArm->TargetArmLength = 200.f;
	SpringArm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 40.f), FRotator(-25.f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Direction = FTransform(GetControlRotation()).TransformVector(Direction);

	AddMovementInput(Direction);

	Direction = FVector::ZeroVector;
}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATestCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATestCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ATestCharacter::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ATestCharacter::InputVertical);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATestCharacter::InputJump);
}

void ATestCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ATestCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ATestCharacter::InputHorizontal(float Value)
{
	Direction.X = Value;
}

void ATestCharacter::InputVertical(float Value)
{
	Direction.Y = Value;
}

void ATestCharacter::InputJump()
{
	Jump();
}