// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Scenario_Manager.h"
#include "Kismet/GameplayStatics.h"
#include "ScenarioManagerWidget.generated.h"
/**
 * 
 */
UCLASS()
class SENSITIVITY_TOOL_API UScenarioManagerWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScenarioName;

	AScenario_Manager* manager_;
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float dt) override;


};
