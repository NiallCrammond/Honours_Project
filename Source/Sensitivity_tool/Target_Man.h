// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "Target_Man.generated.h"

/**
 * 
 */

class ATarget_Spawner;
UCLASS()

class SENSITIVITY_TOOL_API ATarget_Man : public ASkeletalMeshActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	ATarget_Spawner* spawner;


public:
	ATarget_Man();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetHealth(float val);
	void AdjustHealthByAmount(float val);
	float GetHealth();

private:
	float health = 100;
	
};
