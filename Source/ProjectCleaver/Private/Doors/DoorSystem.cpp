// Fill out your copyright notice in the Description page of Project Settings.


#include "Doors/DoorSystem.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDoorSystem::UDoorSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorSystem::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetOwner()->GetActorLocation();
	StartRotator = GetOwner()->GetActorRotation();

	SetComponentTickEnabled(false);
}


// Called every frame
void UDoorSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (DoorState == Opening)
	{
		UpdateLerpAlpha();
		MoveDoor(ApplyOpenCurve());
	}
}

void UDoorSystem::OpenDoor()
{
	if (DoorState == Closed)
	{
		DoorState = Opening;
		SetComponentTickEnabled(true);
	}
}

void UDoorSystem::MoveDoor(float MoveLerpAlpha)
{
	const FVector NewLocation = FVector(FMath::Lerp(StartLocation, EndLocation, MoveLerpAlpha));
	const FRotator NewRotator = FRotator(FMath::Lerp(StartRotator, EndRotator, MoveLerpAlpha));

	GetOwner()->GetRootComponent()->SetWorldLocationAndRotation(NewLocation, NewRotator);
	if (MoveLerpAlpha >= 1)
	{
		DoorState = Open;
		SetComponentTickEnabled(false);
	}
}

void UDoorSystem::UpdateLerpAlpha()
{
	const float Addition = UGameplayStatics::GetWorldDeltaSeconds(this) / OpenDuration;
	LerpAlpha = FMath::Clamp(LerpAlpha + Addition, 0, 1);
}


float UDoorSystem::ApplyOpenCurve() const
{
	return OpenCurve->GetFloatValue(LerpAlpha);
}
