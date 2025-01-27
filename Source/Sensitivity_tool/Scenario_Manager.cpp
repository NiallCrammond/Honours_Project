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

	//Set scenario to be No active Scenario
	base_scenario = no_scenario;
	base_scenario->SetUp();

}

// Called every frame
void AScenario_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Call update on base_scenario(Whatever the current scenario is)
	if (base_scenario)
	{
		base_scenario->Update(DeltaTime);
	
		//Change Scenario after set time elapsed
		if (base_scenario->GetElapsedTime() > random_target_duration)
		{
		base_scenario->CleanUp();	
		base_scenario = no_scenario;
		}
	}

}

Scenario_Base* &AScenario_Manager::GetScenario()
{
	return base_scenario;
}

//Set Scenario by String
void AScenario_Manager::SetScenario(FString scenario_name)
{
	if (scenario_name == "random_man")
	{
		base_scenario = first_scenario;
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("String doesnt match"));

	}

	base_scenario->SetUp();
}



