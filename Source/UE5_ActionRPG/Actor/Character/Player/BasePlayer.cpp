#include "Actor/Character/Player/BasePlayer.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"
#include "Actor/GameMode/MainWorldGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"
#include "Component/EquipComponent.h"
#include "Component/MontageComponent.h"
#include "Actor/Item/Item.h"
#include "Actor/Item/Attachment.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Others/InteractiveActor.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "HUD/InGameHUD.h"
#include "Net/UnrealNetwork.h"

ABasePlayer::ABasePlayer()
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
		ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/_dev/Data/DT/Montage/DT_BasePlayerMontage.DT_BasePlayerMontage'"));
		if (Asset.Succeeded())
		{
			MontageComponent->SetMontageData(Asset.Object);
		}
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
	{
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/_dev/Effect/Death/NS_DeathDissolve.NS_DeathDissolve'"));
		if (NiagaraSystemAsset.Succeeded())
		{
			DeathDissolveEffect = NiagaraSystemAsset.Object; 
		}
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
	Status->StatusModify(Status->HP, -TempDamage);

	// When HP is less or equal than 0 
	if (Status->HP.Current <= 0. && bCanTakeDamage)
	{
		HandlePlayerDeath(); 
		bCanTakeDamage = false; 
	}

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

void ABasePlayer::OnMouseR_Implementation()
{
	MultiOnMouseR();
}

void ABasePlayer::MultiOnMouseR_Implementation()
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

void ABasePlayer::OnShift_Implementation()
{
	if (Status)
	{
		Status->SetSpeed(EWalkSpeedTpye::Run);
	}
}

void ABasePlayer::OffShift_Implementation()
{
	if (Status)
	{
		Status->SetSpeed(EWalkSpeedTpye::Walk);
	}
}

void ABasePlayer::OnEvade()
{
	if (!State->IsIdleMode()) return;
	if (Status->SP.Current < -Status->GetEvadeCost()) return;
	if (bLockOn)
	{
		Status->StatusModify(Status->SP, Status->GetEvadeCost());
		State->SetEvadeMode();
	}
	else
	{
		Status->StatusModify(Status->SP, Status->GetEvadeCost());
		State->SetEvadeMode();
		MontageComponent->PlayAvoid();
	}
}

void ABasePlayer::OnStepBack()
{
	if (!State->IsIdleMode()) return;
	if (Status->SP.Current < -Status->GetEvadeCost()) return;
	Status->StatusModify(Status->SP, Status->GetEvadeCost());
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
		if (Status->SP.Current < -Status->GetAttackCost()) return;

		item->OnDefaultAction();
		Status->StatusModify(Status->SP, Status->GetAttackCost());
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

void ABasePlayer::UpdateHP()
{
	AInGameHUD* MyHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

}

void ABasePlayer::HandlePlayerDeath()
{
	State->SetDeadMode();
	SetActorEnableCollision(false);

	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(GetController());

	if (!BasePlayerController) { return; }

	BasePlayerController->SetIgnoreMoveInput(true);
	BasePlayerController->SetIgnoreLookInput(true);

	if (GetCharacterMovement()->IsMovingOnGround())
	{
		Dead();
	}
	else
	{
		CompletePlayerDeath(BasePlayerController);
	}
}

void ABasePlayer::CompletePlayerDeath(ABasePlayerController* InPlayerController)
{
	if (!InPlayerController) { return; }

	UNiagaraComponent* DeathDissolveComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(DeathDissolveEffect,
		GetMesh(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);

	SetPrimitiveComponentsVisibility(false);

	SetAttachedActorsVisiblity(false);

	DeathDissolveComponent->SetVisibility(true);

	AMainWorldGameMode* GameMode = Cast<AMainWorldGameMode>(UGameplayStatics::GetGameMode(this));

	if (GameMode && InPlayerController)
	{
		GameMode->Respawn(InPlayerController, 3.f);
	}
}

void ABasePlayer::HandlePlayerRevival()
{
	Status->StatusModify(Status->HP, Status->GetMaxHP());
	State->SetIdleMode(); 

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); 
	if (AnimInstance)
	{
		AnimInstance->Montage_Stop(0.f);
	}
}

void ABasePlayer::SetPrimitiveComponentsVisibility(bool bVisible)
{
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	if (Components.Num() == 0) { return;  }

	for (UActorComponent* Component : Components)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component);
		if (PrimitiveComponent)
		{
			PrimitiveComponent->SetVisibility(bVisible, true);
		}
	}
}

void ABasePlayer::SetAttachedActorsVisiblity(bool bVisible)
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	if (AttachedActors.Num() == 0) { return; }

	for (AActor* AttachedActor : AttachedActors)
	{
		TArray<UActorComponent*> AttachedComponents;
		GetComponents(AttachedComponents);

		for (UActorComponent* AttachedComponent : AttachedComponents)
		{
			UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(AttachedComponent);
			if (PrimitiveComponent)
			{
				PrimitiveComponent->SetVisibility(bVisible, true);
			}
		}
	}
}

void ABasePlayer::DestroyAttachedActors()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	if (AttachedActors.Num() == 0) { return; }

	for (AActor* AttachedActor : AttachedActors)
	{
		AttachedActor->Destroy(); 
	}
}

void ABasePlayer::SetAirbone(bool InAirBone)
{
	bAirBone = InAirBone;
	if (InAirBone)
	{
		State->SetHittedMode();
	}
}


void ABasePlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABasePlayer, bAirBone);
}