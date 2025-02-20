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

void UPauseMenuWidget::OnSliderChanged()
{
	ASensitivity_toolCharacter* player = Cast<ASensitivity_toolCharacter>(GetWorld()->GetFirstPlayerController());
	if (!character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No Player"));

	}

	if (!Sens_slider)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("No Sens slider"));

	}

	if (character && Sens_slider)
	{
		float sliderValue = Sens_slider->GetValue();
		character->horizontal_sensitivity = sliderValue;
		FText SensDisplay = FText::AsNumber(sliderValue);
	Sensitivity_Value->SetText(SensDisplay);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor has begun play!"));
		}
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

	if (Sens_slider)
	{
		FScriptDelegate SliderDelegate;
		SliderDelegate.BindUFunction(this, FName("OnSliderChanged"));

		Sens_slider->OnValueChanged.AddUnique(SliderDelegate);
	}

	player_controller = GetWorld()->GetFirstPlayerController();
	character = Cast<ASensitivity_toolCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}


