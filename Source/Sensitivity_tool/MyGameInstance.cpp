// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::CalcualateTrackingStatAverage()
{
	for (auto stats : Tracking_Stat_Array)
	{
		//Accumulate common stats
		tracking_stats.accuracy += stats->accuracy;
		tracking_stats.headshotsHit += stats->headshotsHit;
		tracking_stats.shotsFired += stats->shotsFired; //In this scenario only, shots fired is total amount of frames played
		tracking_stats.shotsHit += stats->shotsHit; // In this scenario only, shots hit is how many frames on target
		tracking_stats.totalTargetsDestroyed += stats->totalTargetsDestroyed;

		//Accumulate tracking stats (These stats monitor how many frames the player over/under aimed)
		tracking_stats.TimeOvertracking += stats->TimeOvertracking;
		tracking_stats.TimeUndertracking += stats->TimeUndertracking;
	}


	//Get tracking performance as a percentage of total time (i.e 72 frames undertracked out of 600 = (72/600) *100 = 12% of time undertracking)
	tracking_stats.TimeOvertracking /= tracking_stats.shotsFired;
	tracking_stats.TimeOvertracking *= 100;
	tracking_stats.TimeUndertracking /= tracking_stats.shotsFired;
	tracking_stats.TimeUndertracking *= 100;


	//divide stats by 3 to get an average over 3 scenarios
	tracking_stats.accuracy /= 3;
	tracking_stats.headshotsHit /= 3;
	tracking_stats.shotsFired /= 3;
	tracking_stats.shotsHit /= 3;
	tracking_stats.totalTargetsDestroyed /= 3;
}

void UMyGameInstance::CalculateFlickingStatAverage()
{
	for (auto stats : Flicking_Array)
	{
		//Accumulate common stats
		flicking_stats.accuracy += stats->accuracy;
		flicking_stats.headshotsHit += stats->headshotsHit;
		flicking_stats.shotsFired += stats->shotsFired;
		flicking_stats.shotsHit += stats->shotsHit;
		flicking_stats.totalTargetsDestroyed += stats->totalTargetsDestroyed;
		
		//Analyse missed shots
		for (const auto& pair : stats->AngleCorrectionHistory)
		{
			float initialOffset = pair.Key; //Initial angle required to turn to hit the target
			float shotOffset = pair.Value; //Angle required to turn after first shot

			//If signs are the same, the player has not yet looked past the target = Underflick
			if (FMath::Sign(initialOffset) == FMath::Sign(shotOffset))
			{
				float percentageUnderFlick = (FMath::Abs(shotOffset) / FMath::Abs(initialOffset)) * 100.f;
				flicking_stats.underFlicks++; // Incremenet Underflick counter
				flicking_stats.averageUnderflick += percentageUnderFlick;//Accumulate percentage of underflick
				UE_LOG(LogTemp, Warning, TEXT("Underflicked by: %f"), percentageUnderFlick)
			}
			else // Overflick
			{
				float turnedDistance = FMath::Abs(initialOffset) + FMath::Abs(shotOffset);
				float percentageOverflick = ((turnedDistance) / FMath::Abs(initialOffset) - 1.f) * 100;
				flicking_stats.overFlicks++; // Increment overflick counter
				flicking_stats.averageOverflick += percentageOverflick; // Accumulate  percentage of overflick
				UE_LOG(LogTemp, Warning, TEXT("Overflicked by: %f"), percentageOverflick);
			}
		}	
	}

	//divide stats by 3 to get an average over 3 scenarios
	flicking_stats.accuracy /= 3;
	flicking_stats.headshotsHit /= 3;
	flicking_stats.shotsFired /= 3;
	flicking_stats.shotsHit /= 3;
	flicking_stats.totalTargetsDestroyed /= 3;

	//Divide percentage accumulation by number of flicks for a average percent error
	flicking_stats.averageOverflick /= flicking_stats.overFlicks;
    flicking_stats.averageUnderflick /= flicking_stats.underFlicks;
}

void UMyGameInstance::CalculateChestStatAverage()
{
	for (auto stats : Chest_Stat_Array)
	{
		//Accumulate common stats
		chest_stats.accuracy += stats->accuracy;
		chest_stats.headshotsHit += stats->headshotsHit;
		chest_stats.shotsFired += stats->shotsFired;
		chest_stats.shotsHit += stats->shotsHit;
		chest_stats.totalTargetsDestroyed += stats->totalTargetsDestroyed;

		//Analyse missed shots
		for (const auto& pair : stats->AngleCorrectionHistory)
		{
			float initialOffset = pair.Key; // Initial angle required to turn to hit the target
			float shotOffset = pair.Value; // Angle required to turn after first shot

			//If signs are the same, the player has not yet looked past the target = Underflick
			if (FMath::Sign(initialOffset) == FMath::Sign(shotOffset))
			{
				float percentageUnderFlick = (FMath::Abs(shotOffset) / FMath::Abs(initialOffset)) * 100.f;
				chest_stats.underFlicks++; //Increment underflick counter
				chest_stats.averageUnderflick += percentageUnderFlick; //Accumulate percentage of underflick
				UE_LOG(LogTemp, Warning, TEXT("Underflicked by: %f"), percentageUnderFlick)
			}
			else // Overflick
			{
				float turnedDistance = FMath::Abs(initialOffset) + FMath::Abs(shotOffset);
				float percentageOverflick = ((turnedDistance) / FMath::Abs(initialOffset) - 1.f) * 100;
				chest_stats.overFlicks++; // Increment overflick counter
				chest_stats.averageOverflick += percentageOverflick; // Accumulate  percentage of overflick
				UE_LOG(LogTemp, Warning, TEXT("Overflicked by: %f"), percentageOverflick);

			}
		}
	}

	//divide stats by 3 to get an average over 3 scenarios
	chest_stats.accuracy /= 3;
	chest_stats.headshotsHit /= 3;
	chest_stats.shotsFired /= 3;
	chest_stats.shotsHit /= 3;
	chest_stats.totalTargetsDestroyed /= 3;

	//Divide percentage accumulation by number of flicks for a average percent error
	chest_stats.averageOverflick /= chest_stats.overFlicks;
	chest_stats.averageUnderflick /= chest_stats.underFlicks;
}


