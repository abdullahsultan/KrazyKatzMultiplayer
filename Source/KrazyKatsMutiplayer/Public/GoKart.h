// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZYKATSMUTIPLAYER_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	/*
		Public Variables
	*/
	UPROPERTY(EditAnywhere)
		float Mass = 1000.0f;
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000.0f;
	
	UPROPERTY(EditAnywhere)
	float MaxDegreePerSecond = 90.0f;


private:
	/*
		private functions
	*/
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UpdateLocationFromVelocity(float DeltaTime);
	void MoveForward(float Value);
	void MoveRight(float Value);
	void ApplyRotation(float DeltaTime);
	
	/*
		Private variables
	*/
	FVector Velocity;
	float Throttle;
	float SteeringThrow;
};
