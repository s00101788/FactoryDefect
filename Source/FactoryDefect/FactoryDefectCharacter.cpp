// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FactoryDefect.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "FactoryDefectCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AFactoryDefectCharacter

AFactoryDefectCharacter::AFactoryDefectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	//Altitude = 100.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;

//	GetCharacterMovement()->AirControl = 0.1;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	// FD 

	PrimaryActorTick.bCanEverTick = true;
	altitudeHoverTarget = 0;
	altitudeCurrent = 0;
}


// Called every frame
void AFactoryDefectCharacter::Tick(float DeltaTime)
{
	if (altitudeHoverTarget > 500)
	{
		altitudeHoverTarget = 500;
	}
	if (altitudeHoverTarget < 0)
	{
		altitudeHoverTarget = 0;
	}


	//RegulateAltitude(currentLocation, targetPosition, theGroundBelow);

	debugStringCharachterFlight = "Debug : current"+ currentLocation.ToString()+" target" +targetPosition.ToString() +" groundPosition"+ theGroundBelow.ToString();

	//float altitudeDifference = altitudeCurrent - altitudeHoverTarget;
	////if (altitudeDifference < 0)
	////	altitudeDifference = altitudeDifference * -1;

	//// if big drop or climb
	//if (altitudeDifference > 20 || altitudeDifference < -20)
	//{
	//	// force gradual altitude change
	//	if (altitudeDifference < 0)
	//	{
	//		currentLocation.Y += 1;
	//	}
	//	else
	//	{
	//		currentLocation.Y += 1;
	//	}
	//}
	//else
	//{
	//	currentLocation = targetPosition;
	//}

	Super::Tick(DeltaTime);

}

FVector AFactoryDefectCharacter::RegulateAltitude(/*FVector currentPos, FVector targetPos, FVector GroundPos*/)
{


	//currentLocation     targetPosition              theGroundBelow

	// should call from   blueprint maybe to better controll trigger order

//	FVector newPos = targetPos;
	float difference = currentLocation.Z - targetPosition.Z;
	//float length;

	//if (difference < 0)
	//	length = difference*-1;
	//else
	//	length = difference;

	if (difference < -150)
	{
		targetPosition.Z = currentLocation.Z - 10;
		//newPos = currentPos;
		//newPos.Z = (newPos.Z - 15);
	}
	if (difference > 150)
	{
		targetPosition.Z = currentLocation.Z + 10;
		//newPos = currentPos;
		//newPos.Z = (newPos.Z - 15);
	}

	//else
	//{
	//	newPos = targetPos;
	//	//newPos.Z = (newPos.Z + altitudeHoverTarget);
	//}

	return targetPosition;
}
//////////////////////////////////////////////////////////////////////////
// Input

void AFactoryDefectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFactoryDefectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFactoryDefectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFactoryDefectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFactoryDefectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFactoryDefectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFactoryDefectCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFactoryDefectCharacter::OnResetVR);
}


void AFactoryDefectCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFactoryDefectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AFactoryDefectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AFactoryDefectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFactoryDefectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFactoryDefectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFactoryDefectCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}

//new float :: float currentJumpHeight = ENGINE_CharacterMovementComponent_generated_h.GetMaxJumpHeight(*(float*)Z_Param__Result);
}


//
//FVector AFactoryDefectCharacter::adjustAltitude(FVector ground, float upPush, FVector position)
//{
//
//
//	if ((ground.Z + upPush) > position.Z)
//	{
//		position.Z++;
//	}
//
//	return position;
//
//	return FVector(position);
//}


//*(float*)Z_Param__Result = this->GetMaxJumpHeight();
ENGINE_CharacterMovementComponent_generated_h
