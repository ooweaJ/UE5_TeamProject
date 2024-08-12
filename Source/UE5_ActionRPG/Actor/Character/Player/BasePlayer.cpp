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
#include "Kismet/KismetSystemLibrary.h"
#include "Others/InteractiveActor.h"

ABasePlayer::ABasePlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
		
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate.Yaw = 720;

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
	
	if (Status && Equip)
	{
		Status->SetSpeed(EWalkSpeedTpye::Walk);
		Equip->SupplyPotion();
		Equip->SetPotionHealAmount(Status->GetMaxHP() * 0.3f);
	}
}

void ABasePlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TickLockOn();
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

void ABasePlayer::OnMouseL()
{
	if (HasAuthority())
	{
		MulticastOnDefaultAction();
	}
	else
	{
		ServerOnMouseL();
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

void ABasePlayer::OnQ()
{
	if (AItem* item = Equip->GetCurrentItem())
	{
		item->OnSkillAction2();
	}
}

void ABasePlayer::OnShift()
{
	if (Status)
	{
		Status->SetSpeed(EWalkSpeedTpye::Run);
	}
}

void ABasePlayer::OffShift()
{
	if (Status)
	{
		Status->SetSpeed(EWalkSpeedTpye::Walk);
	}
}

void ABasePlayer::OnEvade()
{
	if (!State->IsIdleMode()) return;
	if (bLockOn)
	{
		State->SetEvadeMode();
	}
	else
	{
		State->SetEvadeMode();
		MontageComponent->PlayAvoid();
	}
}

void ABasePlayer::OnStepBack()
{
	if (!State->IsIdleMode()) return;
	State->SetStepBackMode();
}

void ABasePlayer::OnInteraction()
{
	if (InteractableObject)
	{
		InteractableObject->OnInteraction();
	}
}

void ABasePlayer::UsePotion()
{
	if (Equip && Equip->CanUsePotion() && Status->GetCurrentHP()!=Status->GetMaxHP())
	{
		Equip->UsePotion();
		Status->StatusModify(Status->HP, Equip->GetPotionHealAmount());
	}
}

void ABasePlayer::ServerOnMouseL_Implementation()
{
	MulticastOnDefaultAction();
}

void ABasePlayer::MulticastOnDefaultAction_Implementation()
{
	if (AItem* item = Equip->GetCurrentItem())
	{
		item->OnDefaultAction();
	}
}

void ABasePlayer::LockOn()
{
	if (!bLockOn)
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> Array;
		Array.Add(EObjectTypeQuery::ObjectTypeQuery3);
		TArray<AActor*> Ignore;
		Ignore.Add(this);
		TArray<FHitResult> MultiHit;
		UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation(), LockOnRadius, Array, false, Ignore, EDrawDebugTrace::ForDuration, MultiHit, true, FLinearColor::Green, FLinearColor::Red, 5.0f);
		AActor* NearestActor = nullptr;
		float NearDistance = 9999.f;
		float Distance;
		for (FHitResult& A : MultiHit)
		{
			Distance = (GetActorLocation() - A.GetActor()->GetActorLocation()).Length();
			if (NearDistance > Distance)
			{
				NearDistance = Distance;
				NearestActor = A.GetActor();
			}
		}
		if (NearestActor)
		{
			TargetActor = NearestActor;
			bLockOn = true;
			NearestActor = nullptr;
		}
	}
	else
	{
		bLockOn = false;
		TargetActor = nullptr;
	}

}

void ABasePlayer::TickLockOn()
{
	ArmPos = SpringArm->GetComponentLocation();
	ActorPos = GetActorLocation();
	if (bLockOn && TargetActor)
	{
			FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation() * FVector(1, 1, 0), TargetActor->GetActorLocation() * FVector(1, 1, 0));
			SetActorRotation(LookRot);
			// SpringArm Set Location
			SpringArm->SetWorldLocation(FMath::Lerp(ArmPos, ActorPos
				, 1.35f * this->GetWorld()->GetDeltaSeconds()));
			Camera->SetWorldLocation(ArmPos + (LookRot.Vector() * LockOnCameraArmLength * -1.0f) + FVector(0, 0, 90));
			Camera->SetWorldRotation(LookRot);
			GetController()->K2_SetActorRotation(LookRot, false);
	}
	else
	{
		SpringArm->SetWorldLocationAndRotation(ActorPos, GetActorForwardVector().Rotation());
		Camera->SetRelativeTransform(FTransform());
	}
	
	
}