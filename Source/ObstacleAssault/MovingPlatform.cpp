// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("World Started..."));

	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	
	RotatePlatform(DeltaTime);
}

void AMovingPlatform:: MovePlatform(float DeltaTime) {


	if (ShouldTurnArround()) {
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else {
		FVector CurrentLoacation = GetActorLocation();
		CurrentLoacation += (PlatformVelocity * DeltaTime);

		SetActorLocation(CurrentLoacation);
	}

}

void AMovingPlatform::RotatePlatform(float DeltaTime) {


	// UE_LOG(LogTemp, Display, TEXT( "%s The PlatForm Has Rotated"),*GetName());
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldTurnArround() const  {
	
	if (GetDistanceMoved() > MoveDistance) return true;
	else return false;
}


double AMovingPlatform::GetDistanceMoved() const {
	return FVector::Distance(StartLocation, GetActorLocation());
}