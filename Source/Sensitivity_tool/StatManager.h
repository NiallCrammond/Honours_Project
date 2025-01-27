// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SENSITIVITY_TOOL_API StatManager
{
public:
	StatManager();
	~StatManager();

	void IncrementShotsFired();
	void IncrementShotsHit();
	void IncrementHeadshotsHit();
	void IncrementTargetsDestroyed();
	void CalculateAccuracy();
	int GetShotsFired();
	int GetShotsHit();
	int GetHeadshotsHit();
	float GetAccuracy();
	int GetTotalTargetsDestroyed();



private:
	int shotsFired;
	int shotsHit;
	int headshotsHit;
	int totalTargetsDestroyed;
	float accuracy;
	float distanceFromHead;
	
};
