// Fill out your copyright notice in the Description page of Project Settings.


#include "StatWidget.h"


void UStatWidget::ProcessFeedback(FString flickFeedback, FString trackingFeedback, FString ChestFeedback)
{

	int CombinedChange = 0;
	int baseChange = 0;
	int ADSChange = 0;

	if (flickFeedback.Contains("decrease by 0"))
	{
		CombinedChange += 0;

	}
	else if (flickFeedback.Contains("decrease by 1"))
	{
		CombinedChange -= 1;
	}
	else if (flickFeedback.Contains("decrease by 2"))
	{
		CombinedChange -= 2;
	}
	else if (flickFeedback.Contains("decrease by 3"))
	{
		CombinedChange -= 3;
	}
	else if (flickFeedback.Contains("increase by 0"))
	{
		CombinedChange += 0;
	}
	else if (flickFeedback.Contains("increase by 1"))
	{
		CombinedChange += 1;
	}
	else if (flickFeedback.Contains("increase by 2"))
	{
		CombinedChange += 2;
	}
	else if (flickFeedback.Contains("increase by 3"))
	{
		CombinedChange += 3;
	}

	if (trackingFeedback.Contains("decrease by 0"))
	{
		CombinedChange += 0;

	}
	else if (trackingFeedback.Contains("decrease by 1"))
	{
		CombinedChange -= 1;
	}
	else if (trackingFeedback.Contains("decrease by 2"))
	{
		CombinedChange -= 2;
	}
	else if (trackingFeedback.Contains("decrease by 3"))
	{
		CombinedChange -= 3;
	}
	else if (trackingFeedback.Contains("increase by 0"))
	{
		CombinedChange += 0;
	}
	else if (trackingFeedback.Contains("increase by 1"))
	{
		CombinedChange += 1;
	}
	else if (trackingFeedback.Contains("increase by 2"))
	{
		CombinedChange += 2;
	}
	else if (trackingFeedback.Contains("increase by 3"))
	{
		CombinedChange += 3;
	}

	if (ChestFeedback.Contains("decrease by 0"))
	{
		CombinedChange += 0;

	}
	else if (ChestFeedback.Contains("decrease by 1"))
	{
		CombinedChange -= 1;
	}
	else if (ChestFeedback.Contains("decrease by 2"))
	{
		CombinedChange -= 2;
	}
	else if (ChestFeedback.Contains("decrease by 3"))
	{
		CombinedChange -= 3;
	}
	else if (ChestFeedback.Contains("increase by 0"))
	{
		CombinedChange += 0;
	}
	else if (ChestFeedback.Contains("increase by 1"))
	{
		CombinedChange += 1;
	}
	else if (ChestFeedback.Contains("increase by 2"))
	{
		CombinedChange += 2;
	}
	else if (ChestFeedback.Contains("increase by 3"))
	{
		CombinedChange += 3;
	}


	baseChange = CombinedChange;
	 ADSChange = baseChange + FMath::Sign(baseChange);

	FString SensChangeSummary = FString::Printf(TEXT("After reviewing the averages of your performances per scenario, we recommend a sensitivity change of : \n Base = %+d \n ADS = %+d"), baseChange, ADSChange);

	FText overallFeedback = FText::FromString(SensChangeSummary);
	OverallFeedbackText->SetText(overallFeedback);

	FText flickName = FText::FromString(flickFeedback);
	FlickFeedbackText->SetText(flickName);

	FText trackName = FText::FromString(trackingFeedback);
	TrackingFeedbackText->SetText(trackName);

	FText chestName = FText::FromString(ChestFeedback);
	ChestFeedbackText->SetText(chestName);
}

void UStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//FText flickName = FText::FromString(TEXT("Flicking"));
	//FlickFeedbackText->SetText(flickName);

	//FText trackName = FText::FromString(TEXT("Tracking"));
	//TrackingFeedbackText->SetText(trackName);

	//FText chestName = FText::FromString(TEXT("Chest"));
	//ChestFeedbackText->SetText(chestName);

}
