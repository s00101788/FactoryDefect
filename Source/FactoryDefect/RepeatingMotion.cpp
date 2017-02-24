// Fill out your copyright notice in the Description page of Project Settings.

#include "FactoryDefect.h"
#include "RepeatingMotion.h"


// Sets default values
ARepeatingMotion::ARepeatingMotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARepeatingMotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARepeatingMotion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector NewLocation = GetActorLocation();
	// makes a sine wave off time for a back and forth
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	//wobble amounts set
	NewLocation.X += DeltaHeight * wobbleX;
	NewLocation.Y += DeltaHeight * wobbleY;
	NewLocation.Z += DeltaHeight * wobbleZ;

	

	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);


}

