// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/PBWeapon.h"

// Sets default values
APBWeapon::APBWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
}

// Called when the game starts or when spawned
void APBWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

