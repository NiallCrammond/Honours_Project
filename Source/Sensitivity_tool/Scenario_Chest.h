// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scenario_Base.h"


class ATarget_Spawner;
class SENSITIVITY_TOOL_API Scenario_Chest : public Scenario_Base 
{
public:
	Scenario_Chest(ATarget_Spawner* spawner);
	~Scenario_Chest();

	// Inherited via Scenario_Base
	void SetUp() override;
	void Update(float dt) override;
	void CleanUp() override;

	float scenario_start_delay = 5.0f;
	float startCountdown= 0.0f;
	bool isDoorOpen = false;
	AActor* _spawnPoint;
	AActor* _door;

};
