// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Patrol.h"

// Sets default values for this component's properties
UPatrol::UPatrol()
{
}

void UPatrol::UpdateDirection()
{
	PatrolIndex = PatrolIndex + PatrolDirection;

	if (PatrolIndex == GetNumberOfSplinePoints() - 1)
	{
		PatrolDirection = -1;
	}
	else if (PatrolIndex == 0)
	{
		PatrolDirection = 1;
	}
}

FVector UPatrol::GetSplinePointLocation()
{
	return GetLocationAtSplinePoint(PatrolIndex, ESplineCoordinateSpace::World);
}

FVector UPatrol::GetRandomSplinePointLocation()
{
	int32 RandomSplinePoint = FMath::RandRange(0, GetNumberOfSplinePoints() - 1);

	return GetLocationAtSplinePoint(RandomSplinePoint, ESplineCoordinateSpace::World);
}
