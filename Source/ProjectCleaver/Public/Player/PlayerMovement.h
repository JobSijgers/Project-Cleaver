#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerMovement.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECTCLEAVER_API APlayerMovement : public ACharacter
{
	GENERATED_BODY()

public:

	APlayerMovement();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* DashAction;
	

	// Movement
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump();
	void StartDash(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintImplementableEvent)
	void DashMovement(FVector DashEndLocation, FVector Velocity);
	
private:

	// Dash
	UPROPERTY()
	bool bCanDash = true;
	
	UPROPERTY(EditAnywhere)
	float DashDistance = 370;

	UPROPERTY(EditAnywhere)
	float DashCooldown = 1.0f;

	FTimerHandle DashCooldownTimerHandle;

	void ResetDashCooldown();
};
