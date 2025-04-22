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
	USlider* Base_Sens_Slider;

	UPROPERTY(meta = (BindWidget))
	USlider* ADS_Sens_Slider;

	UPROPERTY(meta = (BindWidget))
	USlider* Left_Deadzone_Slider;

	UPROPERTY(meta = (BindWidget))
	USlider* Right_Deadzone_Slider;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Base_Sensitivity_Value;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ADS_Sensitivity_Value;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Left_Deadzone_Value;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Right_Deadzone_Value;

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnBaseSensSliderChanged();

	UFUNCTION()
	void OnADSSensSliderChanged();

	UFUNCTION()
	void OnLeftDeadzoneChanged();

	UFUNCTION()
	void OnRightDeadzoneChanged();

	virtual void NativeConstruct() override;


private:
	APlayerController* player_controller;
	ASensitivity_toolCharacter* character;
};
