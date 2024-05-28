// Fill out your copyright notice in the Description page of Project Settings.


#include "Events/EnemyLockedEvent.h"

#include "Enemies/EnemyBase.h"
#include "Health/HealthSystem.h"


// Sets default values for this component's properties
UEnemyLockedEvent::UEnemyLockedEvent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UEnemyLockedEvent::BeginPlay()
{
	Super::BeginPlay();	
	AliveEnemies = Enemies.Num();
	for (const auto Enemy : Enemies)
	{
		UHealthSystem* HealthSystem = Enemy->GetComponentByClass<UHealthSystem>();

		if (!HealthSystem) return;

		HealthSystem->OnDeath.AddDynamic(this, &UEnemyLockedEvent::UpdateThreshold);
	}
}

void UEnemyLockedEvent::UpdateThreshold()
{
	AliveEnemies--;
	if (CheckEventCriteria())
	{
		OnEnemyThresholdReached.Broadcast();
	}
}

bool UEnemyLockedEvent::CheckEventCriteria() const
{
	return AliveEnemies <= EnemyAliveThreshold;
}
