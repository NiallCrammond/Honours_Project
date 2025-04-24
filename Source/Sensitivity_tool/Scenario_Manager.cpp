// Fill out your copyright notice in the Description page of Project Settings.


#include "Scenario_Manager.h"
#include "MyGameInstance.h"

// Sets default values
AScenario_Manager::AScenario_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ScenarioNameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScenarioNameWidget"));
	ScenarioNameWidget->SetupAttachment(RootComponent);
	ScenarioNameWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 100.f));
	ScenarioNameWidget->SetWidgetSpace(EWidgetSpace::World);
	ScenarioNameWidget->SetDrawAtDesiredSize(true);
	ScenarioNameWidget->SetTwoSided(true);
	ScenarioNameWidget->SetPivot(FVector2D(0.5f, 0.5f));
	ScenarioNameWidget->SetWorldRotation(FRotator(0.f, 00.f, 0.f));


}

// Called when the game starts or when spawned
void AScenario_Manager::BeginPlay()
{
	Super::BeginPlay();

	//Create instances of Scenarios 
	first_scenario = new Scenario_Random_Man(_spawner);
	no_scenario = new Scenario_Null();
	tracking_scenario = new Tracking_Scenario(_spawner);
	chest_scenario = new Scenario_Chest(_spawner);

	ScenarioNameWidget->SetPivot(FVector2D(0.5f, 0.5f));
	ScenarioNameWidget->SetWorldRotation(FRotator(0.f, 90.f, 0.f));

	//Set scenario to be No active Scenario
	base_scenario = no_scenario;
	base_scenario->SetUp();

	num_of_chests = _chests.Num(); // retrieve number of chests

	//Loop through exisiting chest in scene, Retrieve their data and store in an array, remove chest once data is saved
	for (int i = 0; i < num_of_chests; i++)
	{
		FChest_Data local_chest;
		local_chest.arc_angle_start = _chests[i]->arc_angle_start;
		local_chest.arc_angle_end = _chests[i]->arc_angle_end;
		local_chest.arc_distance = _chests[i]->arc_distance;
		local_chest.arc_radius = _chests[i]->arc_radius;
		local_chest.chance_to_spawn = _chests[i]->chance_to_spawn;
		local_chest.ChestLocation = _chests[i]->GetActorLocation();
		local_chest.ChestRotation = _chests[i]->GetActorRotation();
		local_chest.time_until_destruct = _chests[i]->time_until_destruct;

		_chests[i]->Destroy();
		data_array.Add(local_chest);
	}

	if (ScenarioNameWidget && ScenarioTextIcon)
	{
		ScenarioNameWidget->SetWidgetClass(ScenarioTextIcon);
	}

	if (feedbackWidgetClass)
	{
		feedbackWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), feedbackWidgetClass);
		
	}
}

// Called every frame
void AScenario_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Check for any deleted/invalud chests and remove from array of chests
	for (int i = 0; i < _chests.Num(); i++)
	{
		AChest* chest = _chests[i];
		if (!IsValid(chest))
		{
			_chests.RemoveAt(i);
		}
	}

	//Call update on base_scenario(Whatever the current scenario is)
	if (base_scenario)
	{
		base_scenario->Update(DeltaTime);
	
		//Change Scenario after set time elapsed
		if (base_scenario->GetElapsedTime() > random_target_duration && base_scenario == first_scenario)
		{
		base_scenario->CleanUp();	
		base_scenario = no_scenario;
		}
		else if (base_scenario->GetElapsedTime() > moving_target_duration && base_scenario == tracking_scenario)
		{
			base_scenario->CleanUp();
			base_scenario = no_scenario;
		}
		//End scenario when no chests left
		else if (base_scenario == chest_scenario && _chests.Num() <=0)
		{
			base_scenario->CleanUp();
			base_scenario = no_scenario;
		}
	}


		UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());



		if (GameInstance->Flicking_Rounds_Played && GameInstance->Tracking_Rounds_Played && GameInstance->Chest_Rounds_Played >= 3)
		{
			if (!statsDisplayed)
			{
				statsDisplayed = true;

				UStatWidget* MyWidget = Cast<UStatWidget>(feedbackWidgetInstance);

				if (MyWidget)
				{
					FString FlickFeedback = GetFlickFeedback();
					FString TrackingFeedback = GetTrackingFeedback();
					FString ChestFeedback = GetChestFeedback();
					MyWidget->ProcessFeedback(FlickFeedback, TrackingFeedback, ChestFeedback);
				}

				feedbackWidgetInstance->AddToViewport();
			}
		}
}

Scenario_Base* &AScenario_Manager::GetScenario()
{
	return base_scenario;
}

//Set Scenario by String
void AScenario_Manager::SetScenario()
{

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(_spawner->GetWorld()->GetGameInstance());

	//Set Scenario based on index, dont  allow i f3 instances of a scenario have been played
	if (base_scenario == no_scenario)
	{
		if (scenario_index == 0 &&GameInstance->Flicking_Rounds_Played <3)
	    {
		base_scenario = first_scenario;
	    }
		else if (scenario_index == 1 && GameInstance->Tracking_Rounds_Played < 3)
	    {
		base_scenario = tracking_scenario;
	    }
		else if (scenario_index == 2 && GameInstance->Chest_Rounds_Played < 3)
		{
		base_scenario = chest_scenario;
		}
		
		base_scenario->SetUp();
	}
}

void AScenario_Manager::NextScenario()
{

	//Increment Scenario Index
	if (scenario_index + 1 < 3)
	{
		scenario_index++;
	}
	else
	{
		scenario_index = 0;
	}
}

void AScenario_Manager::PreviousScenario()
{
	// Decrement Scenario Index
	if (scenario_index == 0)
	{
		scenario_index = 2;
	}
	else
	{
		scenario_index--;
	}
	FString index = FString::Printf(TEXT("Scenario Index: %d"), scenario_index);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, index);
}

FString AScenario_Manager::GetFlickFeedback()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(_spawner->GetWorld()->GetGameInstance());

	FString feedback;

	int underFlicks = GameInstance->flicking_stats.underFlicks;
	int overFlicks = GameInstance->flicking_stats.overFlicks;
	float accuracy = GameInstance->flicking_stats.accuracy;
	int averageOverflick = GameInstance->flicking_stats.averageOverflick;
	int averageUnderflick = GameInstance->flicking_stats.averageUnderflick;

	float totalFlicksMissed = overFlicks + underFlicks;
	float overflickPercentage = 0;
	float underflickPercentage = 0;

	if (accuracy < 75)
	{

		if (totalFlicksMissed > 0)
		{
			if (overFlicks > 0)
			{
				overflickPercentage = ((float)overFlicks / totalFlicksMissed) * 100;
			}

			if (underFlicks > 0)
			{
				underflickPercentage = ((float)underFlicks / totalFlicksMissed) * 100;
			}

			if (overflickPercentage >= 60)
			{
				if (averageOverflick < 10)
				{
					feedback = FString::Printf(TEXT("Flick Scenario: Of your missed shots, %.1f%% were overflicked.\nYou tend to overflick by %d units on average.\nTry a decrease by 0 sensitivity."), overflickPercentage, averageOverflick);
				}

				else if (averageOverflick >= 10 && averageOverflick < 20)
				{
					feedback = FString::Printf(TEXT("Flick Scenario: Of your missed shots, %.1f%% were overflicked.\nYou tend to overflick by %d units on average.\nTry a decrease by 1 sensitivity."), overflickPercentage, averageOverflick);
				}
				else if (averageOverflick >= 20 && averageOverflick < 30)
				{
					feedback = FString::Printf(TEXT("Flick Scenario: Of your missed shots, %.1f%% were overflicked.\nYou tend to overflick by %d units on average.\nTry a decrease by 2 sensitivity."), overflickPercentage, averageOverflick);
				}
				else if (averageOverflick >= 30)
				{
					feedback = FString::Printf(TEXT("Flick Scenario: Of your missed shots, %.1f%% were overflicked.\nYou tend to overflick by %d units on average.\nTry a decrease by 3 sensitivity."), overflickPercentage, averageOverflick);
				}

			}

			else if(underflickPercentage >= 60)
			{
				if (averageUnderflick < 10)
				{
					feedback = FString::Printf(TEXT("Flick Scenario: Of your missed shots, %.1f%% were underflicked.\nYou tend to underflick by %d units on average.\nTry an increase by 0 sensitivity."), underflickPercentage, averageUnderflick);

				}
				else if (averageUnderflick >= 10 && averageUnderflick < 20)
				{
					feedback = FString::Printf(TEXT("Flick Scenario: Of your missed shots, %.1f%% were underflicked.\nYou tend to underflick by %d units on average.\nTry an increase by 1 sensitivity."), underflickPercentage, averageUnderflick);
				}
				else if (averageUnderflick >= 20 && averageUnderflick < 30)
				{
					feedback = FString::Printf(TEXT("Flick Scenario: Of your missed shots, %.1f%% were underflicked.\nYou tend to underflick by %d units on average.\nTry an increase by 2 sensitivity."), underflickPercentage, averageUnderflick);
				}
				else if (averageUnderflick >= 30)
				{
					feedback = FString::Printf(TEXT("Flick Scenario: Of your missed shots, %.1f%% were underflicked.\nYou tend to underflick by %d units on average.\nTry an increase by 3 sensitivity."), underflickPercentage, averageUnderflick);
				}
			}

			else
			{
				feedback = FString::Printf(TEXT("Flick Scenario: Of your missed shots, overflicking vs underflicking was fairly balanced \n We do not advise a change."));
			}
		}
		else
		{
			feedback = FString::Printf(TEXT("Flick Scenario: You had perfect first shot accuracy, well done!"));
		}

	}
	else
	{
		feedback = FString::Printf(TEXT("Flick Scenario: You had a total shot accuracy of %.1f%%.\n Your aim is good and we do not advise a change"), accuracy);
	}
	return feedback;
}

FString AScenario_Manager::GetTrackingFeedback()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(_spawner->GetWorld()->GetGameInstance());

	FString feedback;

	int underFlicks = GameInstance->tracking_stats.underFlicks;
	int overFlicks = GameInstance->tracking_stats.overFlicks;
	float accuracy = GameInstance->tracking_stats.accuracy;
	int timeOverflick = GameInstance->tracking_stats.TimeOvertracking;
	int timeUnderflick = GameInstance->tracking_stats.TimeUndertracking;

	if (accuracy < 75)
	{
		float totalTimeMissed = timeOverflick + timeUnderflick;
		float overtrackPercentage = 0;
		float undertrackPercentage = 0;

		if (totalTimeMissed > 0)
		{
			overtrackPercentage = ((float)timeOverflick / (float)totalTimeMissed) * 100.f;
			undertrackPercentage = ((float)timeUnderflick / (float)totalTimeMissed) * 100.f;

			if (overtrackPercentage >= 60 && overtrackPercentage <70)
			{
				feedback = FString::Printf(TEXT("Tracking Scenario: Of your time not tracking the target, %.1f%% of the time you overtracked.\n Try a decrease by 1 sensitivity."), overtrackPercentage);
			}
			else if (overtrackPercentage >= 70)
			{
				feedback = FString::Printf(TEXT("Tracking Scenario: Of your time not tracking the target, %.1f%% of the time you overtracked.\n Try a decrease by 2 sensitivity."), overtrackPercentage);

			}
			else if (undertrackPercentage >= 60 && undertrackPercentage <70)
			{
				feedback = FString::Printf(TEXT("Tracking Scenario: Of your time not tracking the target, %.1f%% of the time you undertracked.\n Try an increase by 1 sensitivity."), undertrackPercentage);

			}
			else if (undertrackPercentage >= 70)
			{
				feedback = FString::Printf(TEXT("Tracking Scenario: Of your time not tracking the target, %.1f%% of the time you undertracked.\n Try an increase by 2 sensitivity."), undertrackPercentage);

			}
			else
			{
				feedback = FString::Printf(TEXT("Tracking Scenario: Of your time not tracking the target, your undertracking vs overtracking was fairly balanced.\n  We do not advise a change."), undertrackPercentage);

			}
		}

	}	
	else
	{
		feedback = FString::Printf(TEXT("Tracking Scenario: You successfully tracked the target %.1f%% of the time .\n Your aim is good and we do not advise a change."), accuracy);
	}

	return feedback;
}

FString AScenario_Manager::GetChestFeedback()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(_spawner->GetWorld()->GetGameInstance());

	FString feedback;

	int underFlicks = GameInstance->chest_stats.underFlicks;
	int overFlicks = GameInstance->chest_stats.overFlicks;
	float accuracy = GameInstance->chest_stats.accuracy;
	int averageOverflick = GameInstance->chest_stats.averageOverflick;
	int averageUnderflick = GameInstance->chest_stats.averageUnderflick;

	float totalFlicksMissed = overFlicks + underFlicks;
	float overflickPercentage = 0;
	float underflickPercentage = 0;

	if (accuracy < 75)
	{

		if (totalFlicksMissed > 0)
		{
			if (overFlicks > 0)
			{
				overflickPercentage = ((float)overFlicks / totalFlicksMissed) * 100;
			}

			if (underFlicks > 0)
			{
				underflickPercentage = ((float)underFlicks / totalFlicksMissed) * 100;
			}

			if (overflickPercentage >= 60)
			{
				if (averageOverflick < 10)
				{
					feedback = FString::Printf(TEXT("Chest Scenario: Of your missed shots, %.1f%% were overflicked.\nYou tend to overflick by %d units on average.\nTry a decrease by 0 sensitivity."), overflickPercentage, averageOverflick);
				}

				else if (averageOverflick >= 10 && averageOverflick < 20)
				{
					feedback = FString::Printf(TEXT("Chest Scenario: Of your missed shots, %.1f%% were overflicked.\nYou tend to overflick by %d units on average.\nTry a decrease by 1 sensitivity."), overflickPercentage, averageOverflick);
				}
				else if (averageOverflick >= 20 && averageOverflick < 30)
				{
					feedback = FString::Printf(TEXT("Chest Scenario: Of your missed shots, %.1f%% were overflicked.\nYou tend to overflick by %d units on average.\nTry a decrease by 2 sensitivity."), overflickPercentage, averageOverflick);
				}
				else if (averageOverflick >= 30)
				{
					feedback = FString::Printf(TEXT("Chest Scenario: Of your missed shots, %.1f%% were overflicked.\nYou tend to overflick by %d units on average.\nTry a decrease by 3 sensitivity."), overflickPercentage, averageOverflick);
				}

			}

			else if (underflickPercentage >= 60)
			{
				if (averageUnderflick < 10)
				{
					feedback = FString::Printf(TEXT("Chest Scenario: Of your missed shots, %.1f%% were underflicked.\nYou tend to underflick by %d units on average.\nTry an increase by 0 sensitivity."), underflickPercentage, averageUnderflick);

				}
				else if (averageUnderflick >= 10 && averageUnderflick < 20)
				{
					feedback = FString::Printf(TEXT("Chest Scenario: Of your missed shots, %.1f%% were underflicked.\nYou tend to underflick by %d units on average.\nTry an increase by 1 sensitivity."), underflickPercentage, averageUnderflick);
				}
				else if (averageUnderflick >= 20 && averageUnderflick < 30)
				{
					feedback = FString::Printf(TEXT("Chest Scenario: Of your missed shots, %.1f%% were underflicked.\nYou tend to underflick by %d units on average.\nTry an increase by 2 sensitivity."), underflickPercentage, averageUnderflick);
				}
				else if (averageUnderflick >= 30)
				{
					feedback = FString::Printf(TEXT("Chest Scenario: Of your missed shots, %.1f%% were underflicked.\nYou tend to underflick by %d units on average.\nTry an increase by 3 sensitivity."), underflickPercentage, averageUnderflick);
				}
			}

			else
			{
				feedback = FString::Printf(TEXT("Chest Scenario: Of your missed shots, overflicking vs underflicking was fairly balanced \n We do not advise a change."));
			}
		}
		else
		{
			feedback = FString::Printf(TEXT("Chest Scenario: You had perfect first shot accuracy, well done!"));
		}

	}
	else
	{
		feedback = FString::Printf(TEXT("Chest Scenario: You had a total shot accuracy of %.1f%%.\n Your aim is good and we do not advise a change"), accuracy);
	}
	return feedback;
}




