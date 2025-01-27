// Fill out your copyright notice in the Description page of Project Settings.


#include "StatManager.h"

StatManager::StatManager()
{
}

StatManager::~StatManager()
{
}

void StatManager::IncrementShotsFired()
{
	shotsFired++;
}

void StatManager::IncrementShotsHit()
{
	shotsHit++;
}

void StatManager::IncrementHeadshotsHit()
{
	headshotsHit++;
}

void StatManager::IncrementTargetsDestroyed()
{
	totalTargetsDestroyed++;
}

void StatManager::CalculateAccuracy()
{
	accuracy = (shotsHit / shotsFired) * 100;
}

int StatManager::GetShotsFired()
{
	return shotsFired;
}

int StatManager::GetShotsHit()
{
	return shotsHit;
}

int StatManager::GetHeadshotsHit()
{
	return headshotsHit;
}

float StatManager::GetAccuracy()
{
	return accuracy;
}

int StatManager::GetTotalTargetsDestroyed()
{
	return totalTargetsDestroyed;
}

