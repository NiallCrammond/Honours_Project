// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Target_Man.h"
#include "Basic_Roaming_NPC.generated.h"

UCLASS()
class SENSITIVITY_TOOL_API ABasic_Roaming_NPC : public ATarget_Man
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasic_Roaming_NPC();

	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"));
	UBehaviorTree* Tree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
