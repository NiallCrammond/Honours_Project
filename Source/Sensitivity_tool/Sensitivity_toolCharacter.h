// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Scenario_Manager.h"
#include "Logging/LogMacros.h"
#include "Blueprint/UserWidget.h"
#include "Sensitivity_toolCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASensitivity_toolCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	// Aim Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* aimAction;
	//Fire input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;
	//Interact input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	//UI Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> widgetClass;

	UPROPERTY()
	UUserWidget* widgetInstance;

	//Adjustable float for non-critical fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	float base_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	float horizontal_sensitivity= 1;

	//Adjustablle float for critical damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	float headshot_damage;

	//Default socket offset 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FVector default_socket_offset;

	//Aiming socket offset 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FVector aiming_socket_offset;

	//Default FOV when player is not aiminf
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float default_fov;
	
	//FOV used for aiming in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float aiming_fov;

	
	AScenario_Manager* scenarioManager;

public:
	ASensitivity_toolCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	//Functions ued in input mapping for aiming in and out, manipulates camera socket position 
	void AimIn();
	void AimOut();
	void Interact();
	void Fire();
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

