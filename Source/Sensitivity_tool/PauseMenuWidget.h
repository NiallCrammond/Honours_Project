// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
class ASensitivity_toolCharacter;

UCLASS()
class SENSITIVITY_TOOL_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))

	UButton* Resume_Button;

	UPROPERTY(meta = (BindWidget))
	USlider* Sens_slider;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Sensitivity_Value;

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnSliderChanged();
	virtual void NativeConstruct() override;


private:
	APlayerController* player_controller;
	ASensitivity_toolCharacter* character;
};
