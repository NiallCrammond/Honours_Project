// Fill out your copyright notice in the Description page of Project Settings.


#include "Scenario_Random_Man.h"
#include "Target_Spawner.h"
#include "Target_Man.h"
#include "MyGameInstance.h"
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
	GameInstance->rounds_played++;

	//Copy stat data into an array of stats 
	GameInstance->Stat_Array.Add(new Scenario_stats(*stats));

	//If there is 3 rounds played, dispay the average performance
	if (GameInstance->rounds_played >= 3)
	{
		GameInstance->calculateStatAverage();
		FString accuracyString = FString::Printf(TEXT("Shots Fired Average: %f"), GameInstance->average_stats.GetShotsFired());

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, accuracyString);

		FString roundsString = FString::Printf(TEXT("Rounds Played : %d"), GameInstance->rounds_played);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, roundsString);

		float shotsFired = GameInstance->average_stats.GetShotsFired();
		FString firedString = FString::Printf(TEXT("Average Scenario Shots Fired: %f"),  shotsFired);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, firedString);

		float shotsHit = GameInstance->average_stats.GetShotsHit();
		FString hitString = FString::Printf(TEXT("Average Scenario ShotsHit: %f"),shotsHit);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, hitString);

		float targetsDestroyed = GameInstance->average_stats.GetTotalTargetsDestroyed();
		FString targetString = FString::Printf(TEXT("Average Scenario Targets Destroyed: %f"), targetsDestroyed);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, targetString);

		float headshots = GameInstance->average_stats.GetHeadshotsHit();
		FString headshotString = FString::Printf(TEXT("Average Scenario Headshots Hit: %f"), headshots);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, headshotString);

	}
	//Display Single Scenario Stats
	else
	{
		
		FString roundsString = FString::Printf(TEXT("Rounds Played : %d"), GameInstance->rounds_played);
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
