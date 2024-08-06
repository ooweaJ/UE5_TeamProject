#include "Actor/Character/Player/BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"
#include "Component/EquipComponent.h"
#include "Actor/Item/Item.h"

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


