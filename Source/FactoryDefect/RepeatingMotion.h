// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RepeatingMotion.generated.h"

UCLASS()
class FACTORYDEFECT_API ARepeatingMotion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARepeatingMotion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	float RunningTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float wobbleX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float wobbleY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float wobbleZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spin;


};
