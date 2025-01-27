// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sensitivity_toolGameMode.h"
#include "Sensitivity_toolCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASensitivity_toolGameMode::ASensitivity_toolGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
