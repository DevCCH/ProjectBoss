// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PBAnimNotify_AttackHitCheck.h"
#include "Interface/PBAnimationAttackable.h"

void UPBAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IPBAnimationAttackable* Attackable = Cast<IPBAnimationAttackable>(MeshComp->GetOwner());
		if (Attackable)
		{
			Attackable->AttackHitCheck();
		}
	}
}
