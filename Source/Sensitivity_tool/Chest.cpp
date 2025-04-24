// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "Target_Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "Scenario_Manager.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mesh_comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Component"));
	RootComponent = mesh_comp;
	mesh_comp->SetStaticMesh(closed_chest);


    //Set Chest Marker Configs
	ChestIconWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ChestIconWidget"));
	ChestIconWidget->SetupAttachment(RootComponent);
	ChestIconWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 100.f));
	ChestIconWidget->SetWidgetSpace(EWidgetSpace::World);
	ChestIconWidget->SetDrawSize(FVector2D(64.f, 64.f));
	ChestIconWidget->SetTwoSided(true);
	ChestIconWidget->SetPivot(FVector2D(0.5f, 0.5f));
	ChestIconWidget->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	

}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();

	//Find Spawner
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATarget_Spawner::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		_spawner = Cast<ATarget_Spawner>(FoundActors[0]);
	}
	
	// Set Chest icon
	if (ChestIcon && ChestIconWidget)
	{
		ChestIconWidget->SetWidgetClass(ChestIcon);
	}
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Increment chest interact timer
	if (isInteracting)
	{
		interact_timer+= DeltaTime;
    }
	else
	{
		interact_timer = 0;
	}
	
	//If interacted long enough, open chest
	if (interact_timer > time_to_open)
	{
	OpenChest();
	}
	isInteracting = false;

	//Keep track of how long since chest opened
	if (isChestOpen == true)
	{
		opened_timer += DeltaTime;
	}
	
	//Destroy Chest if opened for enough time
	if (opened_timer > time_until_destruct)
	{
		Destroy();
	}

	if (ChestIcon && GetWorld())
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			APawn* Player = PC->GetPawn();
			if (Player)
			{
				//Rotate the Marker to face the player
				FVector ChestLocation = ChestIconWidget->GetComponentLocation();
				FVector PlayerLocation = Player->GetActorLocation();
				FRotator LookAtRotation = (PlayerLocation - ChestLocation).Rotation();
				FRotator WidgetRotation(0.f, LookAtRotation.Yaw, 0.f);
				ChestIconWidget->SetWorldRotation(WidgetRotation);
			}
		}
	}
}

bool AChest::OpenChest()
{
	if (mesh_comp->GetStaticMesh() == closed_chest)
	{
		mesh_comp->SetStaticMesh(open_chest); //Set chest mesh to open
		isChestOpen = true;
		float random_number = FMath::RandRange(1.0f, 100.0f); // generate Random number
		if (random_number < chance_to_spawn) // Compare Random number with spawm shance 
		{
			if (AScenario_Manager* manager = Cast<AScenario_Manager>(UGameplayStatics::GetActorOfClass(GetWorld(), AScenario_Manager::StaticClass())))
			{
				manager->GetScenario()->GetTargets().Add(_spawner->spawnTargetFromChest(this)); // Spawn chest
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool AChest::Interact()
{
	isInteracting = true;
	return isInteracting;
}




