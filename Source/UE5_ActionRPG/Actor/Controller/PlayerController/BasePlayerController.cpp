#include "Actor/Controller/PlayerController/BasePlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Data/Input/InPutDataConfig.h"

ABasePlayerController::ABasePlayerController()
{
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	const UInPutDataConfig* InPutDataConfig = GetDefault<UInPutDataConfig>();
	Subsystem->AddMappingContext(InPutDataConfig->InputMappingContext, 0);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		const UInPutDataConfig* InPutDataConfig = GetDefault<UInPutDataConfig>();
		{
			EnhancedInputComponent->BindAction(InPutDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
			EnhancedInputComponent->BindAction(InPutDataConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::OnLookMouse);
			EnhancedInputComponent->BindAction(InPutDataConfig->Jump, ETriggerEvent::Started, this, &ThisClass::OnJump);
			EnhancedInputComponent->BindAction(InPutDataConfig->MouseL, ETriggerEvent::Started, this, &ThisClass::OnJump);
		}
	}
}

void ABasePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	Player = Cast<ABasePlayer>(aPawn);
	ensure(Player);
}

void ABasePlayerController::OnUnPossess()
{
}

void ABasePlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	APawn* ControlledPawn = GetPawn();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
}

void ABasePlayerController::OnLookMouse(const FInputActionValue& InputActionValue)
{
	const FVector ActionValue = InputActionValue.Get<FVector>();
	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}

void ABasePlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	Player->Jump();
}

void ABasePlayerController::OnMouseL(const FInputActionValue& InputActionValue)
{
	Player->OnAttack();
}
