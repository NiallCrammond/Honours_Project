// Fill out your copyright notice in the Description page of Project Settings.


#include "Roaming_NPC_AIController.h"

#include "Basic_Roaming_NPC.h"

ARoaming_NPC_AIController::ARoaming_NPC_AIController(FObjectInitializer const& ObjectInitializer)
{
}

void ARoaming_NPC_AIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	if (ABasic_Roaming_NPC* const npc = Cast<ABasic_Roaming_NPC>(inPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
