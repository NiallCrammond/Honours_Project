// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Roaming_NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class SENSITIVITY_TOOL_API ARoaming_NPC_AIController : public AAIController
{
	GENERATED_BODY()
	
public:

	explicit ARoaming_NPC_AIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* inPawn)override;
};
