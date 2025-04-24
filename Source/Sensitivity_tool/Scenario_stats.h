// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SENSITIVITY_TOOL_API Scenario_stats
{
public:
	Scenario_stats();
	~Scenario_stats();


	void IncrementShotsFired();
	void IncrementShotsHit();
	void IncrementHeadshotsHit();
	void IncrementTargetsDestroyed();
	void CalculateAccuracy();
	float GetShotsFired();
	float GetShotsHit();
	float GetHeadshotsHit();
	float GetAccuracy();
	float GetTotalTargetsDestroyed();
	void SetShotsFired(float shotsFired);
	void SetShotsHit(float shotsHit);
	void SetHeadshotsHit(float headshotsHit);
	void SetAccuracy(float accuracy);
	void SetTotalTargetsDestroyed(float target_destroyed);
	void ResetStats();


	float shotsFired = 0;
	float shotsHit = 0;
	float headshotsHit = 0;
	float totalTargetsDestroyed = 0;
	float accuracy = 0;
	float overFlicks = 0;
	float underFlicks = 0;
	float averageOverflick = 0;
	float averageUnderflick = 0;
	float TimeOvertracking = 0;
	float TimeUndertracking = 0;

	TArray<TPair<float, float>> AngleCorrectionHistory;

private:

};
