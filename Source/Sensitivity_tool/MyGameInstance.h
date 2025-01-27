// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StatManager.h"
#include "Scenario_stats.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SENSITIVITY_TOOL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();
	
	TArray<Scenario_stats*> Stat_Array;

	void calculateStatAverage();

	Scenario_stats average_stats;
	int rounds_played =0;
private:

};
