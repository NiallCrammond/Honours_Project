// Fill out your copyright notice in the Description page of Project Settings.


#include "Scenario_Chest.h"
#include "Target_Spawner.h"
#include "Target_Man.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Scenario_Manager.h"
#include "Engine/World.h"
#include"Chest.h"

Scenario_Chest::Scenario_Chest(ATarget_Spawner* spawner)
{
	_spawner = spawner;
}

Scenario_Chest::~Scenario_Chest()
{
}

void Scenario_Chest::SetUp()
{
	stats = new Scenario_stats();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Setting up chest scenario"));
	UWorld* World = _spawner->GetWorld();

	if (World)
	{
		if (AScenario_Manager* manager = Cast<AScenario_Manager>(UGameplayStatics::GetActorOfClass(World, AScenario_Manager::StaticClass())))
		{

			_door = manager->door;
			_spawnPoint = manager->spawnPoint;

			if (_spawnPoint)
			{
				World->GetFirstPlayerController()->GetPawn()->SetActorLocation(_spawnPoint->GetActorLocation());
				World->GetFirstPlayerController()->GetPawn()->SetActorRotation(World->GetFirstPlayerController()->GetPawn()->GetActorRotation()+ FRotator(0,0,180));

			}
			
			if (_door)
			{
				startCountdown = 0;
				_door->SetActorHiddenInGame(false);
				_door->SetActorEnableCollision(true);
				isDoorOpen = false;
			}

			for (int i = 0; i < manager->data_array.Num(); i++)
			{
				AChest* new_chest = World->SpawnActor<AChest>(manager->chest_Blueprint);

				if (new_chest)
				{
					new_chest->SetActorLocation(manager->data_array[i].ChestLocation);
					new_chest->SetActorRotation(manager->data_array[i].ChestRotation);
					new_chest->arc_angle_start = manager->data_array[i].arc_angle_start;
					new_chest->arc_angle_end = manager->data_array[i].arc_angle_end;
					new_chest->arc_distance = manager->data_array[i].arc_distance;
					new_chest->arc_radius = manager->data_array[i].arc_radius;
					new_chest->chance_to_spawn = manager->data_array[i].chance_to_spawn;
					new_chest->time_until_destruct = manager->data_array[i].time_until_destruct;
					manager->_chests.Add(new_chest);
				}
			}
		}
		else
		{
			
		}
	}

}

void Scenario_Chest::Update(float dt)
{
	elapsedTime += dt;
	if (isDoorOpen == false)
	{
		startCountdown += dt;
	}

	if (startCountdown > scenario_start_delay && isDoorOpen == false)
	{
		_door->SetActorHiddenInGame(true);
		_door->SetActorEnableCollision(false);
	}

}

void Scenario_Chest::CleanUp()
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
	UWorld* World = _spawner->GetWorld();

	if (World)
	{
		if (AScenario_Manager* manager = Cast<AScenario_Manager>(UGameplayStatics::GetActorOfClass(World, AScenario_Manager::StaticClass())))
		{

			if (manager->initial_spawn_point)
			{
				World->GetFirstPlayerController()->GetPawn()->SetActorLocation(manager->initial_spawn_point->GetActorLocation());
				World->GetFirstPlayerController()->GetPawn()->SetActorRotation(World->GetFirstPlayerController()->GetPawn()->GetActorRotation() + FRotator(0, 0, 180));

			}

			if (_door)
			{
				startCountdown = 0;
				_door->SetActorHiddenInGame(false);
				_door->SetActorEnableCollision(true);
				isDoorOpen = false;
			}
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
		FString firedString = FString::Printf(TEXT("Average Scenario Shots Fired: %f"), shotsFired);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, firedString);

		float shotsHit = GameInstance->average_stats.GetShotsHit();
		FString hitString = FString::Printf(TEXT("Average Scenario ShotsHit: %f"), shotsHit);
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

		float shotsFired = stats->GetShotsFired();
		FString firedString = FString::Printf(TEXT("Previous Scenario Shots Fired: %f"), shotsFired);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, firedString);

		float shotsHit = stats->GetShotsHit();
		FString hitString = FString::Printf(TEXT("Previous Scenario ShotsHit: %f"), shotsHit);
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
