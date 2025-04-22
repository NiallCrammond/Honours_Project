// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scenario_Base.h"
class ATarget_Spawner;
class SENSITIVITY_TOOL_API Tracking_Scenario : public Scenario_Base
{
public:
	Tracking_Scenario(ATarget_Spawner* spawner);
	~Tracking_Scenario();

	float currentTargetTime;

	// Inherited via Scenario_Base
	void SetUp() override;
	void Update(float dt) override;
	void CleanUp() override;
};
