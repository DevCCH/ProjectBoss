// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PBAnimNotify_DodgeEndTriggered.h"
#include "Interface/PBAnimationDodgable.h"

void UPBAnimNotify_DodgeEndTriggered::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IPBAnimationDodgable* dodgable = Cast<IPBAnimationDodgable>(MeshComp->GetOwner());
		if (dodgable)
		{
			dodgable->DodgeEndTriggered();
		}
	}
}