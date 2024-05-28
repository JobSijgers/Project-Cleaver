// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorSystem.generated.h"

UENUM()
enum EDoorState
{
	Closed,
	Opening,
	Open
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTCLEAVER_API UDoorSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDoorSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Called every frame
	UPROPERTY(EditAnywhere)
	float OpenDuration = 1;

	UPROPERTY(EditAnywhere)
	FVector EndLocation;

	UPROPERTY(EditAnywhere)
	FRotator EndRotator;

	UPROPERTY(EditAnywhere)
	UCurveFloat* OpenCurve;

	UFUNCTION(BlueprintCallable)
	void OpenDoor();

private:
	float LerpAlpha = 0;
	FVector StartLocation;
	FRotator StartRotator;
	EDoorState DoorState = Closed;
	void MoveDoor(float MoveLerpAlpha);
	void UpdateLerpAlpha();
	float ApplyOpenCurve() const;
};
