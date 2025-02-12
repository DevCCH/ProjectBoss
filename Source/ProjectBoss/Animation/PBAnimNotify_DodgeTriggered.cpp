// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PBAnimNotify_DodgeTriggered.h"
#include "Interface/PBAnimationDodgable.h"

void UPBAnimNotify_DodgeTriggered::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		IPBAnimationDodgable* dodgable = Cast<IPBAnimationDodgable>(MeshComp->GetOwner());
		if (dodgable != nullptr)
		{
			dodgable->DodgeTriggered();
		}
	}
}
