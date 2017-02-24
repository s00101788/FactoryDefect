// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "RepedativeMotion.generated.h"


// NOT this one


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTORYDEFECT_API URepedativeMotion : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URepedativeMotion();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	float RunningTime;
	
};
