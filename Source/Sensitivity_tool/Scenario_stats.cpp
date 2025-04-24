// Fill out your copyright notice in the Description page of Project Settings.


#include "Scenario_stats.h"

Scenario_stats::Scenario_stats()
{
}

Scenario_stats::~Scenario_stats()
{
}

void Scenario_stats::IncrementShotsFired()
{
	shotsFired++;
}

void Scenario_stats::IncrementShotsHit()
{
	shotsHit++;
}

void Scenario_stats::IncrementHeadshotsHit()
{
	headshotsHit++;
}

void Scenario_stats::IncrementTargetsDestroyed()
{
	totalTargetsDestroyed++;
}

void Scenario_stats::CalculateAccuracy()
{
	accuracy = (shotsHit/shotsFired)*100;
}

float Scenario_stats::GetShotsFired()
{
	return shotsFired;
}

float Scenario_stats::GetShotsHit()
{
	return shotsHit;
}

float Scenario_stats::GetHeadshotsHit()
{
	return headshotsHit;
}

float Scenario_stats::GetAccuracy()
{
	return accuracy;
}

float Scenario_stats::GetTotalTargetsDestroyed()
{
	return totalTargetsDestroyed;
}

void Scenario_stats::SetShotsFired(float shots_fired)
{
	shotsFired = shots_fired;
}

void Scenario_stats::SetShotsHit(float shots_hit)
{
	shotsHit = shots_hit;
}

void Scenario_stats::SetHeadshotsHit(float headshots_hit)
{
	headshotsHit = headshots_hit;
}

void Scenario_stats::SetAccuracy(float acc)
{
	accuracy = acc;
}

void Scenario_stats::SetTotalTargetsDestroyed(float targets_destroyed)
{
	totalTargetsDestroyed = targets_destroyed;
}

void Scenario_stats::ResetStats()
{
	shotsFired = 0;
	shotsHit = 0;
	headshotsHit = 0;
	totalTargetsDestroyed= 0;
	accuracy = 0;
}


