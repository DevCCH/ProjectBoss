// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PBAnimNotify_AttackComboCheck.h"
#include "Character/PBCharacterBase.h"

void UPBAnimNotify_AttackComboCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		auto Player = Cast<APBCharacterBase>(MeshComp->GetOwner());
		if (Player)
		{
			Player->CheckAttackCombo();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Player is null"));
		}
	}
}
