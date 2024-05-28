#include "Player/PlayerMovement.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

APlayerMovement::APlayerMovement()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerMovement::BeginPlay()
{
	Super::BeginPlay();

	// Setting op the enhanced input
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void APlayerMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerMovement::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerMovement::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerMovement::StartJump);
		Input->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerMovement::StartDash);
	}
}

void APlayerMovement::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void APlayerMovement::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void APlayerMovement::StartJump()
{
	Jump();
}

void APlayerMovement::StartDash(const FInputActionValue& Value)
{
	if (!bCanDash) return;

	bool bHasMovementInput = !GetLastMovementInputVector().IsZero();
	FVector Start = GetActorLocation();
	FVector End = GetLastMovementInputVector() * DashDistance + Start;
	FVector3d Velocity = bHasMovementInput ? GetLastMovementInputVector() : GetActorForwardVector();
	FHitResult Hit;
	
	bool bDoesHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);
	FVector3d DashEndLocation = bDoesHit ? Hit.Location + (GetLastMovementInputVector() * -55.0f) : Hit.TraceEnd;
	
	DashMovement(DashEndLocation, Velocity);
	
	bCanDash = false;

	GetWorldTimerManager().SetTimer(DashCooldownTimerHandle, this, &APlayerMovement::ResetDashCooldown, DashCooldown, false);
}

void APlayerMovement::ResetDashCooldown()
{
	bCanDash = true;

	GetWorldTimerManager().ClearTimer(DashCooldownTimerHandle);
}

// if (!GetLastMovementInputVector().IsZero())
// {
// 	FVector Start = GetActorLocation();
// 	FVector End = GetLastMovementInputVector() * DashDistance + Start;

//
// 	FHitResult Hit;
/*
if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
{
	DashMovement(Hit.Location + (GetLastMovementInputVector() * -55.0f), GetLastMovementInputVector());
}
else
{
	DashMovement(Hit.TraceEnd, GetLastMovementInputVector());
}
*/
// bool bDoesHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);
// FVector3d DashStartLocation = bDoesHit ? Hit.Location + (GetLastMovementInputVector() * -55.0f) : Hit.TraceEnd;
// DashMovement(DashStartLocation, GetLastMovementInputVector());
// }
// else
// {
// 	FVector Start = GetActorLocation();
// 	FVector End = GetActorForwardVector() * DashDistance + Start;
//
// 	FHitResult Hit;
// 	
// 	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
// 	{
// 		DashMovement(Hit.Location + (GetLastMovementInputVector() * -55.0f), GetActorForwardVector());
// 	}
// 	else
// 	{
// 		DashMovement(Hit.TraceEnd, GetActorForwardVector());
// 	}
// }
