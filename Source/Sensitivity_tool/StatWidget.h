// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "StatWidget.generated.h"

/**
 * 
 */
UCLASS()
class SENSITIVITY_TOOL_API UStatWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FlickFeedbackText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TrackingFeedbackText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ChestFeedbackText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OverallFeedbackText;

	virtual void NativeConstruct() override;

public:
	void ProcessFeedback(FString flickFeedback, FString trackingFeedback, FString ChestFeedback);
};
