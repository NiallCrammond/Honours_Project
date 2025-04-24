// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scenario_stats.h"

/**
 * 
 */
class ATarget_Spawner;
class ATarget_Man;
class SENSITIVITY_TOOL_API Scenario_Base
{
public:
	Scenario_Base();
	~Scenario_Base();

	//Virtual functions to handle state machine behaviour
	virtual void SetUp() =0;
	virtual void Update(float dt) = 0;
	virtual void CleanUp() = 0;

	//Return references to Stats and Targets to access from other classes
	Scenario_stats*& GetStats();
	TArray<ATarget_Man*>& GetTargets();
	

	float GetElapsedTime();

protected:
	float elapsedTime;
	ATarget_Spawner* _spawner;
	FString ScenarioName;
	Scenario_stats* stats;

	
	TArray<ATarget_Man*> _targets;

private:

};
