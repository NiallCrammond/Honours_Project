// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Delegates/Delegate.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Chest.generated.h"


class ATarget_Spawner;
UCLASS()
class SENSITIVITY_TOOL_API AChest : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	AChest();
	virtual void Tick(float DeltaTime) override;
	bool OpenChest();
	bool Interact();
	void BroadcastChestOpened();

	bool isChestOpen = false;
	bool isInteracting;
	float interact_timer =0;
	float time_to_open =1;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh_comp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* marker_mesh_comp;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* open_chest;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* closed_chest;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* chest_marker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	ATarget_Spawner* _spawner;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float chance_to_spawn =50;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float time_until_destruct;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float opened_timer=0;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float arc_radius;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float arc_distance;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float arc_angle_start;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float arc_angle_end;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ChestIcon;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* ChestIconWidget;

	UPROPERTY()
	UUserWidget* ChestIconInstance;
	
};
