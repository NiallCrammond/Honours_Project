// Copyright Epic Games, Inc. All Rights Reserved.
#include "Sensitivity_toolCharacter.h"
#include "Target_Man.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Scenario_Manager.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyGameInstance.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASensitivity_toolCharacter

ASensitivity_toolCharacter::ASensitivity_toolCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ASensitivity_toolCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	bUseControllerRotationYaw = true;
	
	CameraBoom->SocketOffset = default_socket_offset; // Set Default sockey offset
	FollowCamera->FieldOfView = default_fov; // Set Default Camera FOV
	
	//Find Scenario Manager
	scenarioManager = Cast<AScenario_Manager>(UGameplayStatics::GetActorOfClass(GetWorld(), AScenario_Manager::StaticClass()));

	if (widgetClass)
	{
		widgetInstance = CreateWidget<UUserWidget>(GetWorld(), widgetClass);

		if (widgetInstance)
		{
			widgetInstance->AddToViewport();
		}
	}
	
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASensitivity_toolCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASensitivity_toolCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASensitivity_toolCharacter::Look);

		//Aiming
		EnhancedInputComponent->BindAction(aimAction, ETriggerEvent::Triggered, this, &ASensitivity_toolCharacter::AimIn);
		EnhancedInputComponent->BindAction(aimAction, ETriggerEvent::Completed, this, &ASensitivity_toolCharacter::AimOut);

		//Firing 
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ASensitivity_toolCharacter::Fire);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ASensitivity_toolCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

//Move function binded to input action
void ASensitivity_toolCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

	}
}

//Look Function binded to input action
void ASensitivity_toolCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

//Aim in function binded to input function
void ASensitivity_toolCharacter::AimIn()
{
	if (Controller != nullptr)
	{
		CameraBoom->SocketOffset = aiming_socket_offset;
		FollowCamera->FieldOfView = aiming_fov;
	}
}

//Aim out function binded to Input Action
void ASensitivity_toolCharacter::AimOut()
{
	FollowCamera->FieldOfView = default_fov;
	CameraBoom->SocketOffset = default_socket_offset;
}

//Interact function binded to Input Action
void ASensitivity_toolCharacter::Interact()
{
	FVector StartLocation = FollowCamera->GetComponentLocation(); // Get Camera Location
	FVector ForwardVector = FollowCamera->GetForwardVector(); // Get Forward Direction of Camera

	float RayLength = 100000.0f; // Draw Ray at long distance
	FVector EndLocation = StartLocation + (ForwardVector * RayLength); // End point of ray

	FHitResult hitResult;
	FCollisionQueryParams collisionParams;

	collisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, StartLocation, EndLocation, ECC_Visibility, collisionParams);

	if (bHit)
	{
		AActor* HitActor = hitResult.GetActor();

		if (HitActor)
		{
			if (HitActor->IsA(AScenario_Manager::StaticClass())) // Check if ray collision is with scenario manager
			{
				AScenario_Manager* scenario_manager = Cast<AScenario_Manager>(HitActor);
				if (scenario_manager)
				{
					scenario_manager->SetScenario(FString("random_man")); //Activate scenario
				}
			}
		}
	}
}

void ASensitivity_toolCharacter::Fire()
{
	FVector StartLocation = FollowCamera->GetComponentLocation(); //Get camera location
	FVector ForwardVector = FollowCamera->GetForwardVector(); // Get forward vector of camera 

	float RayLength = 100000.0f; // draw ray at far distance
	FVector EndLocation = StartLocation + (ForwardVector * RayLength); // get end point of ray

	FHitResult hitResult; 
	FCollisionQueryParams collisionParams;

	collisionParams.AddIgnoredActor(this);

	//Ray that runs on channel that only detects scenario manager
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, collisionParams);

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	Scenario_stats* stats = nullptr;

	if (scenarioManager)
	{
	stats = scenarioManager->GetScenario()->GetStats();
	
	if (stats)
	{
		stats->IncrementShotsFired(); // Increase shots fired
	}

	}

	if (bHit)
	{


		AActor* HitActor = hitResult.GetActor();

		if (HitActor)
		{
			if (HitActor->IsA(ATarget_Man::StaticClass())) // Check if the hit actor is a target
			{
				if (scenarioManager)
				{
					if (stats)
					{
						stats->IncrementShotsHit(); //Increment shots
					}

				}
				ATarget_Man* hitTarget = Cast<ATarget_Man>(HitActor);

				USkeletalMeshComponent* skeletalMesh = Cast<USkeletalMeshComponent>(HitActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

				if (skeletalMesh)
				{
					FName HitBoneName = hitResult.BoneName;
					if (!HitBoneName.IsNone())
					{
						//Handle headshots
						if (HitBoneName == "Head")
						{
							if (stats)
							{
								stats->IncrementHeadshotsHit();
							}
							hitTarget->AdjustHealthByAmount(-headshot_damage);
						}
						//handle non-headshots
						else
						{
							FVector hitLocation = hitResult.ImpactPoint;
							FVector headPosition = skeletalMesh->GetBoneLocation("Head", EBoneSpaces::WorldSpace);
							FVector headSpatialOffset = hitLocation - headPosition;
							float dist = headSpatialOffset.Size();
							hitTarget->AdjustHealthByAmount(-base_damage);
						}
					}
				}

			}
			

		}
	}
	//If target is not hit calculate spatial offset
	else
	{
		ATarget_Man* target = Cast<ATarget_Man>(UGameplayStatics::GetActorOfClass(GetWorld(), ATarget_Man::StaticClass()));
		if (target)
		{

			FVector targetPosition = target->GetActorLocation(); // Get the targets location
			FVector RayDirection = (EndLocation - StartLocation).GetSafeNormal(); // Get normalised direction of ray
			FVector TargetToPlayer = targetPosition - StartLocation; // Calculate vector from target to player
			float projectionLength = FVector::DotProduct(TargetToPlayer, RayDirection);// Project targetToPlayer vector onto ray direction to find projection length
			FVector ClosestPointOnRay = StartLocation + RayDirection * projectionLength; // Find closest point on ray using projection length

			//Zero Z values as vertical is not neccesarry 
			FVector closestPointHoriontal = FVector(ClosestPointOnRay.X, ClosestPointOnRay.Y, 0.0f);
			FVector targetPositionHorizontal = FVector(targetPosition.X, targetPosition.Y, 0.0f);

			float distance_x = closestPointHoriontal.X - targetPosition.X; //Calculate horizontal x_axis offset
			float distanceFromTarget = FVector::Distance(closestPointHoriontal, targetPositionHorizontal);

			//Log the offset to screen
			FString spatialOffset = FString::Printf(TEXT("Missed target, closest distance: %f"), distance_x);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, spatialOffset);


		}

	}
	
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, bHit ? FColor::Red : FColor::Green, false, 1.0f, 0, 2.0f);


}
