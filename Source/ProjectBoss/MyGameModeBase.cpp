// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "TestCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = ATestCharacter::StaticClass();
}
