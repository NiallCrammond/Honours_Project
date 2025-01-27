// Fill out your copyright notice in the Description page of Project Settings.


#include "Scenario_Base.h"
Scenario_Base::Scenario_Base()
{
	elapsedTime = 0;
}

Scenario_Base::~Scenario_Base()
{
}

Scenario_stats*& Scenario_Base::GetStats()
{
	return stats;
}

float Scenario_Base::GetElapsedTime()
{
	return elapsedTime;
}

TArray<ATarget_Man*> &Scenario_Base::GetTargets()
{
	return _targets;
}
