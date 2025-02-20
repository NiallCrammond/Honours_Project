// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BFindRandomLocation.h"
#include "NavigationSystem.h"
#include "Roaming_NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BFindRandomLocation::UBTTask_BFindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_BFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ARoaming_NPC_AIController* cont = Cast<ARoaming_NPC_AIController>(OwnerComp.GetAIOwner()))
	{
		if (APawn* npc = cont->GetPawn())
		{

			FVector Origin = npc->GetActorLocation();

			if (UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	 
	
	return EBTNodeResult::Failed;
}
