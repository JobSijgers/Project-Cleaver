// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SplineComponent.h"
#include "Patrol.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTCLEAVER_API UPatrol : public USplineComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPatrol();
	
	// UPROPERTY(EditAnywhere)
	// USplineComponent* PatrolRoute;

	// Patrolling route
	UPROPERTY(EditAnywhere)
	int32 PatrolIndex;

	UPROPERTY(EditAnywhere)
	int32 PatrolDirection = 1;

	UFUNCTION(BlueprintCallable)
	void UpdateDirection();

	UFUNCTION(BlueprintCallable)
	FVector GetSplinePointLocation();

	// Random patrolling points
	UFUNCTION(BlueprintCallable)
	FVector GetRandomSplinePointLocation();
};
