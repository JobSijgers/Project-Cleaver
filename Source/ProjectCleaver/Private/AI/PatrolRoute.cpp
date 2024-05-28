// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PatrolRoute.h"

#include "Components/SplineComponent.h"

// Sets default values
APatrolRoute::APatrolRoute()
{
	PatrolRoute = CreateDefaultSubobject<USplineComponent>(FName("PatrolRoute"));
	SetRootComponent(PatrolRoute);
}

void APatrolRoute::UpdateDirection()
{
	PatrolIndex = PatrolIndex + PatrolDirection;

	if (PatrolIndex == PatrolRoute->GetNumberOfSplinePoints() - 1)
	{
		PatrolDirection = -1;
	}
	else if (PatrolIndex == 0)
	{
		PatrolDirection = 1;
	}
}

FVector APatrolRoute::GetSplinePointLocation()
{
	return PatrolRoute->GetLocationAtSplinePoint(PatrolIndex, ESplineCoordinateSpace::World);
}

FVector APatrolRoute::GetRandomSplinePointLocation()
{
	int32 RandomSplinePoint = FMath::RandRange(0, PatrolRoute->GetNumberOfSplinePoints() - 1);

	return PatrolRoute->GetLocationAtSplinePoint(RandomSplinePoint, ESplineCoordinateSpace::World);
}
