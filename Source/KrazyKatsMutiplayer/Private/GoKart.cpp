// Fill out your copyright notice in the Description page of Project Settings.


#include "GoKart.h"
#include "Components/InputComponent.h"

// Sets default values
AGoKart::AGoKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Force;
	Force = GetActorForwardVector() * MaxDrivingForce * Throttle;
	Force += GetAirResistance();
	Force += GetRollingResistance();

	FVector Accelaration = Force / Mass;
	Velocity = Velocity + (Accelaration * DeltaTime);
	
	float AccelarationDueToGravity = -GetWorld()->GetGravityZ() / 100;

	ApplyRotation(DeltaTime);

	UpdateLocationFromVelocity(DeltaTime);
}

void AGoKart::ApplyRotation(float DeltaTime)
{
	float DeltaLocation = FVector::DotProduct(GetActorForwardVector(), Velocity) * DeltaTime;
	float RotaionAngle = DeltaLocation / MinTurningRadius * SteeringThrow;
	FQuat RotationDelta(GetActorUpVector(), RotaionAngle);
	Velocity = RotationDelta.RotateVector(Velocity);
	AddActorWorldRotation(RotationDelta);
}

FVector AGoKart::GetAirResistance()
{
	return -Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}

FVector AGoKart::GetRollingResistance()
{
	float AccelarationDueToGravity = -GetWorld()->GetGravityZ() / 100;
	float NormalForce = Mass * AccelarationDueToGravity;
	return -Velocity.GetSafeNormal() * RollingResistanceCoefficient * NormalForce;
}

void AGoKart::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * DeltaTime * 100;
	FHitResult Hit;
	AddActorWorldOffset(Translation, true, &Hit);
	if (Hit.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &AGoKart::Server_MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGoKart::Server_MoveRight);

}


void AGoKart::Server_MoveForward_Implementation(float Value)
{
	Throttle = Value;
}

bool AGoKart::Server_MoveForward_Validate(float Value)
{
	return FMath::Abs(Value) <= 1;
}

void AGoKart::Server_MoveRight_Implementation(float Value)
{
	SteeringThrow = Value;
}

bool AGoKart::Server_MoveRight_Validate(float Value)
{
	return FMath::Abs(Value) <= 1;
}