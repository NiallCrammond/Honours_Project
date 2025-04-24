// Fill out your copyright notice in the Description page of Project Settings.


#include "ScenarioManagerWidget.h"

void UScenarioManagerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	manager_ = Cast<AScenario_Manager>(UGameplayStatics::GetActorOfClass(GetWorld(), AScenario_Manager::StaticClass()));
	FText name = FText::FromString(TEXT("Flick"));
	ScenarioName->SetText(name);
}

void UScenarioManagerWidget::NativeTick(const FGeometry& MyGeometry, float dt)
{
	Super::NativeTick(MyGeometry, dt);

	UE_LOG(LogTemp, Warning, TEXT("TICKING"));

	if (manager_->scenario_index == 0)
	{
		FText name = FText::FromString(TEXT("Flick"));
		ScenarioName->SetText(name);
	}
	
	if (manager_->scenario_index == 1)
	{
		FText name = FText::FromString(TEXT("Track"));
		ScenarioName->SetText(name);
	}

	if (manager_->scenario_index == 2)
	{
		FText name = FText::FromString(TEXT("Chest"));
		ScenarioName->SetText(name);
	}
}
