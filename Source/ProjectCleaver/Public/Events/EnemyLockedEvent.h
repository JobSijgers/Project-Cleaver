// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyLockedEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyThresholdReached);

class AEnemyBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTCLEAVER_API UEnemyLockedEvent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyLockedEvent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnEnemyThresholdReached OnEnemyThresholdReached;

	UPROPERTY(EditAnywhere)
	int16 EnemyAliveThreshold;
	UPROPERTY(EditAnywhere)
	TArray<AEnemyBase*> Enemies;

	UFUNCTION()
	void UpdateThreshold();

	bool CheckEventCriteria() const;

private:
	int16 AliveEnemies;
};
