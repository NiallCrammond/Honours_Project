// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scenario_Base.h"
/**
 * 
 */
class SENSITIVITY_TOOL_API Scenario_Null : public Scenario_Base
{
public:
	Scenario_Null();
	~Scenario_Null();

	// Inherited via Scenario_Base
	void SetUp() override;
	void Update(float dt) override;
	void CleanUp() override;
};
