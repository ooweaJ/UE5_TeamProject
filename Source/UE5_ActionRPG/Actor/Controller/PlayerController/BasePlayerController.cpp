#include "Actor/Controller/PlayerController/BasePlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Data/Input/InPutDataConfig.h"
#include "BaseGameplayTags.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

ABasePlayerController::ABasePlayerController()
{
	
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!Subsystem) return;
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
			EnhancedInputComponent->BindAction(InPutDataConfig->MouseL, ETriggerEvent::Started, this, &ThisClass::OnMouseL);
			EnhancedInputComponent->BindAction(InPutDataConfig->MouseR, ETriggerEvent::Started, this, &ThisClass::OnMouseR);
			EnhancedInputComponent->BindAction(InPutDataConfig->MouseL, ETriggerEvent::Completed, this, &ThisClass::OffMouseL);
			EnhancedInputComponent->BindAction(InPutDataConfig->MouseR, ETriggerEvent::Completed, this, &ThisClass::OffMouseR);
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
	ABasePlayer* ControlledPawn = Cast<ABasePlayer>(GetPawn());

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotator(0, ControlledPawn->Camera->GetComponentRotation().Yaw,0).Vector();
	const FVector RightDirection = FRotator(0, ControlledPawn->Camera->GetComponentRotation().Yaw+90, 0).Vector();

	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);

	float AngleDampingSpeed = 1;

	if (Player)
	{
		if (Player->WalkingDirectionAngle < 45 && Player->WalkingDirectionAngle > -45)
		{
			AngleDampingSpeed = 1.0;

		}
		else
		{
			AngleDampingSpeed = 0.75;
		}
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y * AngleDampingSpeed);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X * AngleDampingSpeed);

		Player->ForwardInput = ForwardDirection * MovementVector.Y;
		Player->RightInput = RightDirection * MovementVector.X;
		Player->MoveDirection = (Player->ForwardInput + Player->RightInput).GetSafeNormal();
		Player->WalkingDirectionAngle = UKismetAnimationLibrary::CalculateDirection(Player->MoveDirection, Player->GetActorRotation());
		if (!Player->bLockOn)
		{
			Player->SetActorRotation(UKismetMathLibrary::RLerp(Player->GetActorRotation(), Player->MoveDirection.Rotation(), GWorld->GetDeltaSeconds() * Player->CharacterRotationAlphaLinearValue, true));
		}
	}
}

void ABasePlayerController::OnLookMouse(const FInputActionValue& InputActionValue)
{
	if (!Player->bLockOn)
	{
		const FVector ActionValue = InputActionValue.Get<FVector>();
		AddYawInput(ActionValue.X);
		AddPitchInput(ActionValue.Y);
	}
}

void ABasePlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	if (Player)
		Player->Jump();
}

void ABasePlayerController::OnMouseL(const FInputActionValue& InputActionValue)
{
	if (Player)
		Player->OnMouseL();
}

void ABasePlayerController::OnMouseR(const FInputActionValue& InputActionValue)
{
	if(Player)
		Player->OnMouseR();
}

void ABasePlayerController::OffMouseL(const FInputActionValue& InputActionValue)
{
	if (Player)
		Player->OnMouseL();
}

void ABasePlayerController::OffMouseR(const FInputActionValue& InputActionValue)
{
	if (Player)
		Player->OnMouseR();
}
