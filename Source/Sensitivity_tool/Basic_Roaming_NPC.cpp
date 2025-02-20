// Fill out your copyright notice in the Description page of Project Settings.


#include "Basic_Roaming_NPC.h"
#include "Kismet/GameplayStatics.h"
#include "Target_Spawner.h"
#include "MyGameInstance.h"
#include "Scenario_Manager.h"

// Sets default values
ABasic_Roaming_NPC::ABasic_Roaming_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ABasic_Roaming_NPC::BeginPlay()
{
	Super::BeginPlay();
	
	spawner = Cast<ATarget_Spawner>(UGameplayStatics::GetActorOfClass(GetWorld(), ATarget_Spawner::StaticClass()));

}

// Called every frame
void ABasic_Roaming_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input

UBehaviorTree* ABasic_Roaming_NPC::GetBehaviorTree() const
{
	return Tree;
}

