// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sensitivity_toolCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
void UPauseMenuWidget::OnResumeButtonClicked()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		PC->SetPause(false);
		this->RemoveFromViewport();
		PC->bShowMouseCursor = false;
	}
}

void UPauseMenuWidget::OnBaseSensSliderChanged()
{
	ASensitivity_toolCharacter* player = Cast<ASensitivity_toolCharacter>(GetWorld()->GetFirstPlayerController());
	if (!character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No Player"));

	}

	if (!Base_Sens_Slider)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No Sens slider"));

	}

	if (character && Base_Sens_Slider)
	{
		float sliderValue = Base_Sens_Slider->GetValue();
		character->Base_Sensitivity = sliderValue;
		FText SensDisplay = FText::AsNumber(sliderValue);
	    Base_Sensitivity_Value->SetText(SensDisplay);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor has begun play!"));
		}
	}
}

void UPauseMenuWidget::OnADSSensSliderChanged()
{
	ASensitivity_toolCharacter* player = Cast<ASensitivity_toolCharacter>(GetWorld()->GetFirstPlayerController());
	if (!character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No Player"));

	}

	if (!ADS_Sens_Slider)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No Sens slider"));

	}

	if (character && ADS_Sens_Slider)
	{
		float sliderValue = ADS_Sens_Slider->GetValue();
		character->ADS_Sensitivity = sliderValue;
		FText SensDisplay = FText::AsNumber(sliderValue);
		ADS_Sensitivity_Value->SetText(SensDisplay);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor has begun play!"));
		}
	}
}

void UPauseMenuWidget::OnLeftDeadzoneChanged()
{
	ASensitivity_toolCharacter* player = Cast<ASensitivity_toolCharacter>(GetWorld()->GetFirstPlayerController());
	if (!character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No Player"));

	}

	if (!Left_Deadzone_Slider)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No left deadzone slider"));

	}

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
	ASensitivity_toolCharacter* player = Cast<ASensitivity_toolCharacter>(GetWorld()->GetFirstPlayerController());
	if (!character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No Player"));

	}

	if (!Right_Deadzone_Slider)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No right deadzone slider"));

	}

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



	player_controller = GetWorld()->GetFirstPlayerController();
	character = Cast<ASensitivity_toolCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}


