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

	void MoveForward(float Value);
	void MoveRight(float Value);



	/*
		Public Variables
	*/
	UPROPERTY(EditAnywhere)
		float Mass = 1000.0f;
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000.0f;
	
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10.0f;
	
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16.0f;
	
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = 0.015f;


private:
	/*
		private functions
	*/
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UpdateLocationFromVelocity(float DeltaTime);
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveForward(float Value);
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRight(float Value);
	void ApplyRotation(float DeltaTime);
	FVector GetAirResistance();
	FVector GetRollingResistance();
	
	/*
		Private variables
	*/
	FVector Velocity;
	float Throttle;
	float SteeringThrow;

	UPROPERTY(Replicated)
		FVector ReplicatedLocation;

	UPROPERTY(Replicated)
		FRotator ReplicatedRotation;
};
