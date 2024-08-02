#include "Actor/Character/Player/BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"
#include "Component/EquipComponent.h"
#include "Component/MontageComponent.h"
#include "Actor/Item/Item.h"
#include "Kismet/KismetMathLibrary.h"

ABasePlayer::ABasePlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	{
		USkeletalMeshComponent* mesh = GetMesh();
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
		if (!Asset.Succeeded()) return;

		mesh->SetSkeletalMesh(Asset.Object);
		mesh->SetRelativeLocation(FVector(0, 0, -88));
		mesh->SetRelativeRotation(FRotator(0, -90, 0));
	}
	{
		SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
		SpringArm->SetupAttachment(RootComponent);

		Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
		Camera->SetupAttachment(SpringArm);

		SpringArm->SetRelativeLocation(FVector(0, 0, 90));
		SpringArm->TargetArmLength = 300.f;
		SpringArm->bDoCollisionTest = true;
		SpringArm->bUsePawnControlRotation = true;
	}
	Tags.Add("Player");
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Status && State->IsIdleMode())
		RegenStamina(DeltaTime);
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABasePlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float TempDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	/* TODO */

	return TempDamage;
}

void ABasePlayer::OnDodgeStarted(float DirectionAngle)
{
	if (!HasEnoughStamina() || !State->IsIdleMode()) 
	{
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("Can not Dodge"), true);
		return;
	}
	if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		MontageComponent->PlayAvoid(SelectSlot());
		if (Status)
		{
			Status->DecreaseStamina(Status->GetDodgeCost());
		}
		// Temp
		OnDodgeEnd();
	}
}

void ABasePlayer::OnDodgeEnd()
{
	State->SetIdleMode();
}

void ABasePlayer::OnMouseL()
{
	if (AItem* item = Equip->GetCurrentItem())
	{
		item->OnDefaultAction();
	}
}

void ABasePlayer::OnMouseR()
{
	if (AItem* item = Equip->GetCurrentItem())
	{
		item->OnSkillAction();
	}
}

void ABasePlayer::OffMouseL()
{
	if (AItem* item = Equip->GetCurrentItem())
	{
		item->OffDefaultAction();
	}
}

void ABasePlayer::OffMouseR()
{
	if (AItem* item = Equip->GetCurrentItem())
	{
		item->OffSkillAction();
	}
}

bool ABasePlayer::HasEnoughStamina()
{
	return Status && Status->GetStamina() > Status->GetDodgeCost();
}

void ABasePlayer::RegenStamina(float DeltaTime)
{
	EStateType CurrentType = State->GetCurrentMode();
	//if(CurrentType == EStateType::Idle)
	{
		//Status->SetStaminaRegen(40.f);
		Status->IncreaseStamina(Status->GetStaminaRegen() * DeltaTime);
	}
	//else
	//{
	//	Status->SetStaminaRegen(20.f);
	//	Status->IncreaseStamina(Status->GetStaminaRegen() * DeltaTime);
	//}
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, FString::SanitizeFloat(Status->GetStamina()));
}

FName ABasePlayer::SelectSlot()
{
	int64 LocalIndex = 0;
	if (UKismetMathLibrary::InRange_FloatFloat(WalkingDirectionAngle, -45, 45))
	{
		LocalIndex = 0;
	}
	if (UKismetMathLibrary::InRange_FloatFloat(WalkingDirectionAngle, 45, 135, false))
	{
		LocalIndex = 1;
	}
	if (UKismetMathLibrary::InRange_FloatFloat(WalkingDirectionAngle, 135, 180, false) || 
		UKismetMathLibrary::InRange_FloatFloat(WalkingDirectionAngle, -180, -135, true, false))
	{
		LocalIndex = 2;
	}
	if (UKismetMathLibrary::InRange_FloatFloat(WalkingDirectionAngle, -135, -45, false, true))
	{
		LocalIndex = 3;
	}
	FName SlotName;
	switch (LocalIndex)
	{
	case 0:
		return SlotName = TEXT("FWD");
	case 1:
		return SlotName = TEXT("Right");
	case 2:
		return SlotName = TEXT("BWD");
	case 3:
		return SlotName = TEXT("Left");
	default:
		return SlotName = TEXT("");
	}
}

