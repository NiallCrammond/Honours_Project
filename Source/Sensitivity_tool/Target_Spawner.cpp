// Fill out your copyright notice in the Description page of Project Settings.


#include "Target_Spawner.h"
#include "Engine/World.h"
#include "Target_Spawner.h"
#include "Target_Man.h"
#include "MyGameInstance.h"


// Sets default values
ATarget_Spawner::ATarget_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATarget_Spawner::BeginPlay()
{
	Super::BeginPlay();
	//spawnTarget();
}

void ATarget_Spawner::spawnTarget()
{
	FActorSpawnParameters spawmParams;
	ATarget_Man* spawnedTarget = GetWorld()->SpawnActor<ATarget_Man>(target_Blueprint, spawnPoint, spawnRotation, spawmParams); //Spawn target
	Targets.Add(spawnedTarget); //Add taregt to array
	totalTargetsSpawned++;
	
}

ATarget_Man* ATarget_Spawner::spawnTargetInBox()
{
	if (spawnArea)
	{
		FVector BoxOrigin = spawnArea->GetActorLocation();
		FVector BoxExtent = spawnArea->GetComponentsBoundingBox().GetExtent();

		//Generate random point within a volume
		float randomX = FMath::RandRange(BoxOrigin.X - BoxExtent.X, BoxOrigin.X + BoxExtent.X);
		float randomY = FMath::RandRange(BoxOrigin.Y - BoxExtent.Y, BoxOrigin.Y + BoxExtent.Y);
		float randomZ = FMath::RandRange(BoxOrigin.Z - BoxExtent.Z, BoxOrigin.Z + BoxExtent.Z);

		//Place player at bottom of volume
		float positionZ = BoxOrigin.Z - BoxExtent.Z;

		FVector randomPoint = FVector(randomX, randomY,positionZ);
		FActorSpawnParameters spawmParams;

		ATarget_Man* spawnedTarget = GetWorld()->SpawnActor<ATarget_Man>(target_Blueprint,randomPoint , spawnRotation, spawmParams);
		Targets.Add(spawnedTarget);
		totalTargetsSpawned++;

		return spawnedTarget;
	}

	return nullptr;
}

TArray<ATarget_Man*>& ATarget_Spawner::GetTargets()
{
	return Targets;
}

// Called every frame
void ATarget_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

