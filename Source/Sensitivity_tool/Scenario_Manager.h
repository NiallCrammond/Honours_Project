// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scenario_Base.h"
#include "Scenario_Null.h"
#include "Scenario_Random_Man.h"
#include "Tracking_Scenario.h"
#include "Target_Spawner.h"
#include "Chest.h"
#include "Scenario_Chest.h"
#include "StatWidget.h"
#include "Scenario_Manager.generated.h"

 USTRUCT()
 struct FChest_Data
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector ChestLocation;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	FRotator ChestRotation;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float arc_radius;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float arc_distance;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float arc_angle_start;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float arc_angle_end;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float chance_to_spawn = 50;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float time_until_destruct;

};


UCLASS()
class SENSITIVITY_TOOL_API AScenario_Manager : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AScenario_Manager();
	//Pointers for scenarios
	Scenario_Base* base_scenario;
	Scenario_Random_Man* first_scenario;
	Scenario_Null* no_scenario;
	Tracking_Scenario* tracking_scenario;
	Scenario_Chest* chest_scenario;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int num_of_chests = 0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	Scenario_Base* &GetScenario(); // Returns current Scenario
	void SetScenario();
	void NextScenario();
	void PreviousScenario();
	
	FString GetFlickFeedback();
	FString GetTrackingFeedback();
	FString GetChestFeedback();

	bool statsDisplayed = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ScenarioTextIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* ScenarioNameWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	ATarget_Spawner* _spawner; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	TArray<AChest*> _chests;
	
	UPROPERTY(EditAnywhere, Category = "Scenario's", meta = (AllowPrivateAccess = "true"))
	TArray<FChest_Data> data_array;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> chest_Blueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario's", meta = (AllowPrivateAccess = "true"))
	float random_target_duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario's", meta = (AllowPrivateAccess = "true"))
	float moving_target_duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario's", meta = (AllowPrivateAccess = "true"))
	AActor* door;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario's", meta = (AllowPrivateAccess = "true"))
	AActor* spawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scenario's", meta = (AllowPrivateAccess = "true"))
	AActor* initial_spawn_point;
	
	int scenario_index = 0; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> feedbackWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UUserWidget* feedbackWidgetInstance;

};
