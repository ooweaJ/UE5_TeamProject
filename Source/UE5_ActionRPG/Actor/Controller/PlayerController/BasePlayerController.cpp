#include "Actor/Controller/PlayerController/BasePlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Data/Input/InPutDataConfig.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGameplayTags.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ABasePlayerController::ABasePlayerController()
{
	
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	/*UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	const UInPutDataConfig* InPutDataConfig = GetDefault<UInPutDataConfig>();
	if (Subsystem)
		Subsystem->AddMappingContext(InPutDataConfig->InputMappingContext, 0);
	else
		UE_LOG(LogTemp, Warning, TEXT("Subsystem is nullptr"));*/
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PlayerController = It->Get();
		if (PlayerController && PlayerController->IsLocalController())
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
			const UInPutDataConfig* InPutDataConfig = GetDefault<UInPutDataConfig>();

			if (Subsystem)
			{
				Subsystem->AddMappingContext(InPutDataConfig->InputMappingContext, 0);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Subsystem is nullptr for player controller: %s"), *PlayerController->GetName());
			}
		}
	}
	
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
		}
	}
}

void ABasePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

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
	float AngleDampingSpeed = 1;
	ABasePlayer* BasePlayer = Cast<ABasePlayer>(ControlledPawn);
	if (!BasePlayer) return;
	if (BasePlayer->WalkingDirectionAngle < 45 && BasePlayer->WalkingDirectionAngle > -45)
	{
		AngleDampingSpeed = 1.0;
	}
	else
	{
		AngleDampingSpeed = 0.75;
	}

	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y * AngleDampingSpeed);
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X * AngleDampingSpeed);

	BasePlayer->ForwardInput = ForwardDirection * MovementVector.Y;
	BasePlayer->RightInput = RightDirection * MovementVector.X;
	BasePlayer->MoveDirection = (BasePlayer->ForwardInput + BasePlayer->RightInput).GetSafeNormal();
	BasePlayer->WalkingDirectionAngle = UKismetAnimationLibrary::CalculateDirection(BasePlayer->MoveDirection, BasePlayer->GetActorRotation());
	if (!BasePlayer->bLockOn)
	{
		BasePlayer->SetActorRotation(UKismetMathLibrary::RLerp(BasePlayer->GetActorRotation(), BasePlayer->MoveDirection.Rotation(), GWorld->GetDeltaSeconds() * BasePlayer->CharacterRotationAlphaLinearValue, true));
	}
}

void ABasePlayerController::OnLookMouse(const FInputActionValue& InputActionValue)
{
	const FVector ActionValue = InputActionValue.Get<FVector>();
	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}

void ABasePlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	ABasePlayer* PlayerCharacter = Cast<ABasePlayer>(GetPawn());
	if (!PlayerCharacter) 
	{
		ensure(false);
		return;
	}
	UBaseAbilitySystemComponent* BAS = Cast<UBaseAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent());
	BAS->ActiveAbility(BaseGameplayTags::Input_Action_Jump);
}

void ABasePlayerController::OnMouseL(const FInputActionValue& InputActionValue)
{
	//Player->OnAttackL();
}

void ABasePlayerController::OnMouseR(const FInputActionValue& InputActionValue)
{
	//Player->OnAttackR();
}
