// Fill out your copyright notice in the Description page of Project Settings.

#include "FactoryDefect.h"
#include "RepedativeMotion.h"


// Sets default values for this component's properties
URepedativeMotion::URepedativeMotion()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URepedativeMotion::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URepedativeMotion::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

//	var x = GetRootComponent(this);

	//FVector NewLocation = GetActorLocation();
	//float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	//NewLocation.X += DeltaHeight * 200.0f;       //Scale our height by a factor of what you type
	//RunningTime += DeltaTime;
	//SetActorLocation(NewLocation);

	// ...
}

