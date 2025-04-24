// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SENSITIVITY_TOOL_API Tracking_Stats
{
public:
	Tracking_Stats();
	~Tracking_Stats();

	float ElapsedTime;
	float TimeOnTarget;
	float TrackingAccuracy;
	TArray<float> Offset_Array;
    
};
