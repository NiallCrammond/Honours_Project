// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sensitivity_toolCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
void UPauseMenuWidget::OnResumeButtonClicked()
{
	if (UGameplayStatics::IsGamePaused(GetWorld())) // If game is paused, resume game and remove UI From viewport
	{
		player_controller->SetPause(false);
		this->RemoveFromViewport();
		player_controller->bShowMouseCursor = false;
	}
}

void UPauseMenuWidget::OnBaseSensSliderChanged()
{
	if (character && Base_Sens_Slider)
	{
		float sliderValue = Base_Sens_Slider->GetValue(); //Retrieve value of slider
		character->Base_Sensitivity = sliderValue; //Set Unaimed sens to value of slider
		FText SensDisplay = FText::AsNumber(sliderValue); // Get slider value as text
		Base_Sensitivity_Value->SetText(SensDisplay); // Update Text to display sensitivity
	}
}

void UPauseMenuWidget::OnADSSensSliderChanged()
{
	if (character && ADS_Sens_Slider)
	{
		float sliderValue = ADS_Sens_Slider->GetValue(); //Retrieve value of slider
		character->ADS_Sensitivity = sliderValue; //Set ADS sens to value of slider
		FText SensDisplay = FText::AsNumber(sliderValue); // Get slider value as text
		ADS_Sensitivity_Value->SetText(SensDisplay); // Update Text to display sensitivity
	}
	
}

void UPauseMenuWidget::OnLeftDeadzoneChanged()
{
	if (character && Left_Deadzone_Slider)
	{
		float sliderValue = Left_Deadzone_Slider->GetValue();
		character->Left_Stick_Deadzone= sliderValue;
		FText Left_Deadzone_Display = FText::AsNumber(sliderValue);
		Left_Deadzone_Value->SetText(Left_Deadzone_Display);
	}
}

void UPauseMenuWidget::OnRightDeadzoneChanged()
{
	if (character && Right_Deadzone_Slider)
	{
		float sliderValue = Right_Deadzone_Slider->GetValue();
		character->Right_Stick_Deadzone = sliderValue;
		FText Right_Deadzone_Display = FText::AsNumber(sliderValue);
		Right_Deadzone_Value->SetText(Right_Deadzone_Display);
	}
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Get References for Player controller and character
	player_controller = GetWorld()->GetFirstPlayerController();
	character = Cast<ASensitivity_toolCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	//Bind fucntions to UI elements using delegates
	if (Resume_Button)
	{
		FScriptDelegate ResumeDelegate;
		ResumeDelegate.BindUFunction(this, FName("OnResumeButtonClicked"));

		// Add the delegate to the OnClicked event
		Resume_Button->OnClicked.AddUnique(ResumeDelegate);
	}

	if (Base_Sens_Slider)
	{
		FScriptDelegate SliderDelegate;
		SliderDelegate.BindUFunction(this, FName("OnBaseSensSliderChanged"));

		Base_Sens_Slider->OnValueChanged.AddUnique(SliderDelegate);
	}

	if (ADS_Sens_Slider)
	{
		FScriptDelegate SliderDelegate;
		SliderDelegate.BindUFunction(this, FName("OnADSSensSliderChanged"));

		ADS_Sens_Slider->OnValueChanged.AddUnique(SliderDelegate);
	}

	if (Left_Deadzone_Slider)
	{
		FScriptDelegate LeftDeadzoneSliderDelegate;
		LeftDeadzoneSliderDelegate.BindUFunction(this, FName("OnLeftDeadzoneChanged"));

		Left_Deadzone_Slider->OnValueChanged.AddUnique(LeftDeadzoneSliderDelegate);
	}

	if (Right_Deadzone_Slider)
	{
		FScriptDelegate RightDeadzoneSliderDelegate;
		RightDeadzoneSliderDelegate.BindUFunction(this, FName("OnRightDeadzoneChanged"));

		Right_Deadzone_Slider->OnValueChanged.AddUnique(RightDeadzoneSliderDelegate);
	}

}


