// Fill out your copyright notice in the Description page of Project Settings.


#include "Target_Man.h"
#include "Target_Spawner.h"
#include "Scenario_Manager.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
ATarget_Man::ATarget_Man()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATarget_Man::BeginPlay()
{
	Super::BeginPlay();

	//Find spawner
	spawner = Cast<ATarget_Spawner>(UGameplayStatics::GetActorOfClass(GetWorld(), ATarget_Spawner::StaticClass()));
}

// Called every frame
void ATarget_Man::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Handle Target Death
	if (health < 0)
	{
		spawner->GetTargets().Remove(this); // remove targets from spawner array
		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
		AScenario_Manager* Scenario_Manager = Cast<AScenario_Manager>(UGameplayStatics::GetActorOfClass(GetWorld(), AScenario_Manager::StaticClass()));
		
		if (Scenario_Manager)
		{
			Scenario_Manager->GetScenario()->GetTargets().Remove(this); // remove target from scenario manager array
			Scenario_stats* stats = Scenario_Manager->GetScenario()->GetStats();
			
			if (stats)
			{
				stats->IncrementTargetsDestroyed();
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("There is no ScenarioManager detected"));
		}

		Destroy();
	}
}

void ATarget_Man::SetHealth(float val)
{
	health = val;
}

void ATarget_Man::AdjustHealthByAmount(float val)
{
	health += val;
}

float ATarget_Man::GetHealth()
{
	return health;
}



