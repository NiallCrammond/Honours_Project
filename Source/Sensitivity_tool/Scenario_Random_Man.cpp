// Fill out your copyright notice in the Description page of Project Settings.


#include "Scenario_Random_Man.h"
#include "Target_Spawner.h"
#include "Target_Man.h"
#include "MyGameInstance.h"
#include "StatWidget.h"
#include "Scenario_Manager.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"

Scenario_Random_Man::Scenario_Random_Man(ATarget_Spawner* spawner)
{
	_spawner = spawner;
}

Scenario_Random_Man::~Scenario_Random_Man()
{
}

void Scenario_Random_Man::SetUp()
{
	stats = new Scenario_stats();
}

void Scenario_Random_Man::Update(float dt)
{
	elapsedTime += dt;
//If there isn't an active target, spawn one;
	if (_targets.Num() < 1)
	{
		_targets.Add(_spawner->spawnTargetInBox());
	}
}

void Scenario_Random_Man::CleanUp()
{
	//Destroy active targets and remove from array
	if (_targets.Num() >= 1)
	{
		for (auto target : _targets)
		{
			 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Removing Target"));
			_targets.Remove(target);
			target->Destroy();
			elapsedTime = 0;
		}
	}
	stats->CalculateAccuracy();
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(_spawner->GetWorld()->GetGameInstance());
	GameInstance->Flicking_Rounds_Played++;

	//Copy stat data into an array of stats 
	GameInstance->Flicking_Array.Add(new Scenario_stats(*stats));

	//If there is 3 rounds played, dispay the average performance
	if (GameInstance->Flicking_Rounds_Played >= 3)
	{
		GameInstance->CalculateFlickingStatAverage();
		FString accuracyString = FString::Printf(TEXT("Shots Fired Average: %f"), GameInstance->flicking_stats.GetShotsFired());

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, accuracyString);

		FString roundsString = FString::Printf(TEXT("Rounds Played : %d"), GameInstance->Flicking_Rounds_Played);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, roundsString);

		float shotsFired = GameInstance->flicking_stats.GetShotsFired();
		FString firedString = FString::Printf(TEXT("Average Scenario Shots Fired: %f"),  shotsFired);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, firedString);

		float shotsHit = GameInstance->flicking_stats.GetShotsHit();
		FString hitString = FString::Printf(TEXT("Average Scenario ShotsHit: %f"),shotsHit);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, hitString);

		float targetsDestroyed = GameInstance->flicking_stats.GetTotalTargetsDestroyed();
		FString targetString = FString::Printf(TEXT("Average Scenario Targets Destroyed: %f"), targetsDestroyed);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, targetString);

		float headshots = GameInstance->flicking_stats.GetHeadshotsHit();
		FString headshotString = FString::Printf(TEXT("Average Scenario Headshots Hit: %f"), headshots);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, headshotString);

		float overflick = GameInstance->flicking_stats.averageOverflick;
		FString overflickString = FString::Printf(TEXT("Average Overflick Percentage: %f"), overflick);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, overflickString);


		float underflick = GameInstance->flicking_stats.averageUnderflick;
		FString underflickString = FString::Printf(TEXT("Average UnderFlick Percentage: %f"), underflick);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, underflickString);

		//AScenario_Manager* manager = Cast<AScenario_Manager>(UGameplayStatics::GetActorOfClass(_spawner->GetWorld(), AScenario_Manager::StaticClass()));
		//UStatWidget* MyWidget = Cast<UStatWidget>(manager->feedbackWidgetInstance);

		//
		//if (MyWidget)
		//{
		//	FString FlickFeedback =  manager->GetFlickFeedback();
		//	MyWidget->ProcessFeedback(FlickFeedback, "Tracking", "Chest Scenario");
		//}

		//manager->feedbackWidgetInstance->AddToViewport();

	}
	//Display Single Scenario Stats
	else
	{
		
		FString roundsString = FString::Printf(TEXT("Rounds Played : %d"), GameInstance->Flicking_Rounds_Played);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, roundsString);

		float shotsFired= stats->GetShotsFired();
		FString firedString = FString::Printf(TEXT("Previous Scenario Shots Fired: %f"),  shotsFired);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, firedString);

		float shotsHit = stats->GetShotsHit();
		FString hitString = FString::Printf(TEXT("Previous Scenario ShotsHit: %f"),shotsHit);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, hitString);

		float accuracy = stats->GetAccuracy();
		FString accuracyString = FString::Printf(TEXT("Previous Scenario Accuracy: %f"), accuracy);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, accuracyString);

		float targetsDestroyed = stats->GetTotalTargetsDestroyed();
		FString targetString = FString::Printf(TEXT("Previous Scenario Targets Destroyed: %f"), targetsDestroyed);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, targetString);

		float headshots = stats->GetHeadshotsHit();
		FString headshotString = FString::Printf(TEXT("Previous Scenario Headshots Hit: %f"), headshots);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, headshotString);


	}
	
	delete stats;
}
