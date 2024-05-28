// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/HealthSystem.h"

// Sets default values for this component's properties
UHealthSystem::UHealthSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UHealthSystem::TakeDamage(int32 amount)
{
	CurrentHealth -= abs(amount);

	OnDamageTaken.Broadcast(CurrentHealth);
	OnHealthUpdate.Broadcast(GetNormalizedHealth());

	if (CurrentHealth <= 0)
		OnDeath.Broadcast();
	
}

void UHealthSystem::HealHealth(int32 HealAmount)
{
	const int16 newHealth = FMath::Clamp(CurrentHealth + abs(HealAmount), 0,MaxHealth );

	if (newHealth == CurrentHealth)
		return;

	CurrentHealth = newHealth;
	OnHeal.Broadcast(CurrentHealth);
	OnHealthUpdate.Broadcast(GetNormalizedHealth());

}
