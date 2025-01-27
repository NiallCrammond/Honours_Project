// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Engine/TriggerBox.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Animation/SkeletalMeshActor.h"
#include "Target_Spawner.generated.h"

class ATarget_Man;

UCLASS()

class SENSITIVITY_TOOL_API ATarget_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget_Spawner();
	void spawnTarget();
	ATarget_Man* spawnTargetInBox();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> target_Blueprint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Spawning")
	FVector spawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	FRotator spawnRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	ATriggerBox* spawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<ATarget_Man*> Targets;
	virtual void BeginPlay() override;
	


public:	
	// Called every frame
	TArray<ATarget_Man*> &GetTargets();

	virtual void Tick(float DeltaTime) override;

private:
	int totalTargetsSpawned;
	int numberOfTargetsActive;
	//TArray<ASkeletalMeshActor*> Targets;
};
