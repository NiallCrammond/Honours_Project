// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include  "Scenario_Base.h"

class ATarget_Spawner;
class SENSITIVITY_TOOL_API Scenario_Random_Man : public Scenario_Base
{
public:
	Scenario_Random_Man(ATarget_Spawner* spawner);
	~Scenario_Random_Man();

	// Inherited via Scenario_Base
	void SetUp() override;
	void Update(float dt) override;
	void CleanUp() override;

};
