// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::calculateStatAverage()
{
	//Loop through stats and add all results up
	for (auto stats : Stat_Array)
	{
		average_stats.accuracy += stats->accuracy;
		average_stats.distanceFromHead += stats->distanceFromHead;
		average_stats.headshotsHit += stats->headshotsHit;
		average_stats.shotsFired += stats->shotsFired;
		average_stats.shotsHit += stats->shotsHit;
		average_stats.totalTargetsDestroyed += stats->totalTargetsDestroyed;
	}

	//divide stats by 3 to get an average over 3 scenarios
		average_stats.accuracy /= 3;
		average_stats.distanceFromHead /= 3;
		average_stats.headshotsHit /= 3;
		average_stats.shotsFired /= 3;
		average_stats.shotsHit /= 3;
		average_stats.totalTargetsDestroyed /= 3;

}


