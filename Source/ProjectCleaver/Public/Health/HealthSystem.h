// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, int32, NewHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeal, int32, NewHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdate, float, HealthNormalized);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTCLEAVER_API UHealthSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDamageTaken OnDamageTaken;

	UPROPERTY(BlueprintAssignable)
	FOnHeal OnHeal;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
	FOnHealthUpdate OnHealthUpdate;

	UPROPERTY(EditAnywhere)
	int32 MaxHealth;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int32 amount);

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return CurrentHealth <= 0; }

	UFUNCTION(BlueprintCallable)
	float GetNormalizedHealth() const { return (float)CurrentHealth / (float)MaxHealth; }

	UFUNCTION(BlueprintCallable)
	void HealHealth(int32 HealAmount);

private:
	int32 CurrentHealth;
};
