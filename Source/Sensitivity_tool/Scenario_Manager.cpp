// Fill out your copyright notice in the Description page of Project Settings.


#include "Scenario_Manager.h"

// Sets default values
AScenario_Manager::AScenario_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	//Set scenario to be No active Scenario
	base_scenario = no_scenario;
	base_scenario->SetUp();

	num_of_chests = _chests.Num();
	FString chest_num = FString::Printf(TEXT("Chests: %d"), _chests.Num());
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, chest_num);

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
}

// Called every frame
void AScenario_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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
		else if (base_scenario == chest_scenario && _chests.Num() <=0)
		{
			base_scenario->CleanUp();
			base_scenario = no_scenario;
		}
	}

	/*FString chest_num = FString::Printf(TEXT("Chests: %d"), _chests.Num());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, chest_num);*/

}

Scenario_Base* &AScenario_Manager::GetScenario()
{
	return base_scenario;
}

//Set Scenario by String
void AScenario_Manager::SetScenario(FString scenario_name)
{
	if (base_scenario == no_scenario)
	{
		if (scenario_index == 0)
	    {
		base_scenario = first_scenario;
	    }
		else if (scenario_index == 1)
	    {
		base_scenario = tracking_scenario;
	    }
		else if (scenario_index == 2)
		{
		base_scenario = chest_scenario;
		}
		
		base_scenario->SetUp();
	}
}

void AScenario_Manager::NextScenario()
{
	if (scenario_index + 1 < scenario_names.Num())
	{
		scenario_index++;
	}
	else
	{
		scenario_index = 0;
	}

	FString index = FString::Printf(TEXT("Scenario Index: %d"), scenario_index);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, index);
}

void AScenario_Manager::PreviousScenario()
{
	if (scenario_index == 0)
	{
		scenario_index = scenario_names.Num()-1;
	}
	else
	{
		scenario_index--;
	}
	FString index = FString::Printf(TEXT("Scenario Index: %d"), scenario_index);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, index);
}




