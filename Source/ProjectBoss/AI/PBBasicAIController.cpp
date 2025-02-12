// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PBBasicAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

APBBasicAIController::APBBasicAIController()
{
}

void APBBasicAIController::RunAI()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		UE_LOG(LogTemp, Log, TEXT("YES"));
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());
		auto LocalPlayer = GetWorld()->GetFirstPlayerController();
		if (LocalPlayer)
		{
			auto Player = LocalPlayer->GetPawn();
			if (Player)
			{
				Blackboard->SetValueAsObject(TEXT("TargetPawn"), Player);
				bool RunResult = RunBehaviorTree(BTAsset);
				ensure(RunResult);
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("NONO"));
		}
	}
}

void APBBasicAIController::StopAI()
{
	auto BehaviorTreeComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComp)
	{
		BehaviorTreeComp->StopTree();
	}
}

void APBBasicAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APBBasicAIController::RunAI, 3);
}
