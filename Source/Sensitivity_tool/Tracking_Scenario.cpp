// Fill out your copyright notice in the Description page of Project Settings.


#include "Tracking_Scenario.h"
#include "Target_Spawner.h"
#include "Target_Man.h"
#include "MyGameInstance.h"
#include "Engine/World.h"

Tracking_Scenario::Tracking_Scenario(ATarget_Spawner* spawner)
{
	_spawner = spawner;
}

Tracking_Scenario::~Tracking_Scenario()
{
}

void Tracking_Scenario::SetUp()
{
	stats = new Scenario_stats();
}

void Tracking_Scenario::Update(float dt)
{
	elapsedTime += dt;
	currentTargetTime += dt;


		for (auto target : _targets)
		{
			if ((target->GetVelocity().X < 10) && (target->GetVelocity().X > -10) && currentTargetTime >0.5)
			{

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Removing Target"));
			_targets.Remove(target);
			target->Destroy();
			currentTargetTime = 0;
			}
		}
	

	//If there isn't an active target, spawn one;
	if (_targets.Num() < 1)
	{
		ATarget_Man* target = _spawner->spawnMovingTargetInBox();
		_targets.Add(target);
		
		currentTargetTime = 0;
	}
}

void Tracking_Scenario::CleanUp()
{
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
	GameInstance->Tracking_Rounds_Played++;

	//Copy stat data into an array of stats 
	GameInstance->Tracking_Stat_Array.Add(new Scenario_stats(*stats));

	//If there is 3 rounds played, dispay the tracking performance
	if (GameInstance->Tracking_Rounds_Played >= 3)
	{

		FString roundsString = FString::Printf(TEXT("Rounds Played : %d"), GameInstance->Tracking_Rounds_Played);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, roundsString);

		float shotsFired = GameInstance->tracking_stats.GetShotsFired();
		FString firedString = FString::Printf(TEXT("Average Scenario Shots Fired: %f"), shotsFired);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, firedString);

		float shotsHit = GameInstance->tracking_stats.GetShotsHit();
		FString hitString = FString::Printf(TEXT("Average Scenario ShotsHit: %f"), shotsHit);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, hitString);

		GameInstance->CalcualateTrackingStatAverage();
		FString accuracyString = FString::Printf(TEXT("Average Accuracy: %f"), GameInstance->tracking_stats.GetAccuracy());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, accuracyString);

		float underTrack = GameInstance->tracking_stats.TimeUndertracking;
		FString underString = FString::Printf(TEXT("Percentage Of time Undertracking: %f"), underTrack);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, underString);

		float overTrack = GameInstance->tracking_stats.TimeOvertracking;
		FString overString = FString::Printf(TEXT("Percentage Of time Undertracking: %f"), overTrack);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, overString);
	}
	//Display Single Scenario Stats
	else
	{

		FString roundsString = FString::Printf(TEXT("Rounds Played : %d"), GameInstance->Tracking_Rounds_Played);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, roundsString);

		float shotsFired = stats->GetShotsFired();
		FString firedString = FString::Printf(TEXT("Previous Scenario Shots Fired: %f"), shotsFired);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, firedString);

		float shotsHit = stats->GetShotsHit();
		FString hitString = FString::Printf(TEXT("Previous Scenario ShotsHit: %f"), shotsHit);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, hitString);

		float accuracy = stats->GetAccuracy();
		FString accuracyString = FString::Printf(TEXT("Previous Scenario Accuracy: %f"), accuracy);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, accuracyString);

		float underTrack = stats->TimeUndertracking;
		FString underString = FString::Printf(TEXT("Percentage Of time Undertracking: %f"), underTrack);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, underString);

		float overTrack = stats->TimeOvertracking;
		FString overString = FString::Printf(TEXT("Percentage Of time Undertracking: %f"), overTrack);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, overString);
	}

	delete stats;
}
