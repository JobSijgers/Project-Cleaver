// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

class USplineComponent;

UCLASS()
class PROJECTCLEAVER_API APatrolRoute : public AActor
{
	GENERATED_BODY()

	APatrolRoute();

public:
	UPROPERTY(EditAnywhere)
	USplineComponent* PatrolRoute;

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
