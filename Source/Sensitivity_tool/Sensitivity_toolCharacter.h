// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Scenario_Manager.h"
#include "Logging/LogMacros.h"
#include "Blueprint/UserWidget.h"
#include "SPauseMenuWidget.h"
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
	
	//INPUT VARIABLES
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NextScenarioAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PreviousScenarioAction;

	
	//UI VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CrossairWidgetClass;

	UPROPERTY()
	UUserWidget* CrosshairWidgetInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UUserWidget* PauseMenuWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> RightArrowWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UUserWidget* RightArrowWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LeftArrowWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UUserWidget* LeftArrowWidgetInstance;




public:
	float isAiming = false;

	//Adjustable float for non-critical fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	float base_damage= 35;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	float Base_Sensitivity= 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	float ADS_Sensitivity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	float Left_Stick_Deadzone = 0.05;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	float Right_Stick_Deadzone = 0.05;

	//Adjustablle float for critical damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	float headshot_damage =70;

	//Default socket offset 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FVector default_socket_offset = FVector(0.f, 0.f, 0.f);

	//Aiming socket offset 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FVector aiming_socket_offset =  FVector(0.f,0.f,0.f);

	//Default FOV when player is not aiminf
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float default_fov = 0;
	
	//FOV used for aiming in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float aiming_fov = 0;


	AScenario_Manager* scenarioManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float angle_required_to_turn = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	bool hasFirstShotAtTargetFired = false;
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
	void PauseGame();
	void NextScenario();
	void PreviousScenario();

	virtual void Tick(float dt) override;
			
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	//Exponential functions that return turn rate
	float CalculateADSSensitivity(float sensitivity);
	float CalculateNormalSensitivity(float sensitivity);

	bool lookCalled = false;
	float elapsedTime = 0;
	float continousRotation=0;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

