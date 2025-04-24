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
	
	//Array stores individual scneario run stats
	TArray<Scenario_stats*> Flicking_Array;
	TArray<Scenario_stats*> Tracking_Stat_Array;
	TArray<Scenario_stats*> Chest_Stat_Array;

	//Functions for Calculating average stats  per scenario after 3 attempts
	void CalcualateTrackingStatAverage();
	void CalculateFlickingStatAverage();
	void CalculateChestStatAverage();

	//Average stats of each scenario
	Scenario_stats tracking_stats;
	Scenario_stats flicking_stats;
	Scenario_stats chest_stats;

	//Round count of each scenario
	int Tracking_Rounds_Played =0;
	int Flicking_Rounds_Played = 0;
	int Chest_Rounds_Played = 0;

private:

};
