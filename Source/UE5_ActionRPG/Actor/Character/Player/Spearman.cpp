// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/Player/Spearman.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/SkinnedAssetCommon.h"
#include "Animation/AnimBlueprint.h"
#include "Actor/Item/Weapon/SpearProjectile.h"
#include "Actor/Item/Weapon/SpearWeapon.h"
#include "Actor/Item/Attachment.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Notifies/AN_ThrowSpear.h"
#include "Components/BoxComponent.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"

ASpearman::ASpearman()
{
	{
		static ConstructorHelpers::FClassFinder<UAnimInstance> ABPClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Retargeted_Asset/ABP_Spearman.ABP_Spearman_C'"));
		ensure(ABPClass.Class); 
		GetMesh()->SetAnimInstanceClass(ABPClass.Class); 
	}
}

ASpearWeapon* ASpearman::GetSpearWeapon() const
{
	if (DefaultItemClass)
	{
		ASpearWeapon* SpearWeapon = Cast<ASpearWeapon>(DefaultItemClass); 
		return SpearWeapon; 
	}
	else
	{
		check(false); 
		return nullptr; 
	}
}

void ASpearman::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform); 

	if (USkeletalMeshComponent* CharacterMesh = Cast<USkeletalMeshComponent>(GetMesh()))
	{
		const TArray<FSkeletalMaterial>& SkeletalMaterials = CharacterMesh->GetSkinnedAsset()->GetMaterials(); 
		const int32 MaterialNum = SkeletalMaterials.Num(); 
		for (int32 i = 0; i < MaterialNum; ++i)
		{
			UMaterialInstanceDynamic* MID = CharacterMesh->CreateDynamicMaterialInstance(i, SkeletalMaterials[i].MaterialInterface); 
			MID->SetVectorParameterValue(TEXT("Color"), FVector4(0.f, 1.f, 0.f, 1.f));
		}
	}

	DefaultItemClass = ASpearWeapon::StaticClass(); 
	
	SetupSpearProjectile();
}

void ASpearman::BeginPlay()
{
	Super::BeginPlay(); 

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); 
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ASpearman::OnMontageEnded); 
	}
}

void ASpearman::SetupSpearProjectile()
{
	FActorSpawnParameters SpawnParams; 
	SpawnParams.Owner = this; 
	
	FName SocketName = TEXT("Hand_Spear_R"); 
	const FTransform& SocketTransform = GetMesh()->GetSocketTransform(SocketName, ERelativeTransformSpace::RTS_ParentBoneSpace);
	const FVector& SocketLocation = SocketTransform.GetLocation(); 
	
	SpearProjectile = GetWorld()->SpawnActor<ASpearProjectile>(SocketLocation, FRotator::ZeroRotator, SpawnParams);
	SpearProjectile->SetActorEnableCollision(false);

	UProjectileMovementComponent* ProjectileMovement = SpearProjectile->FindComponentByClass<UProjectileMovementComponent>();
	if (ProjectileMovement)
	{
		ProjectileMovement->SetActive(false); 
	}

	SpearProjectile->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	SpearProjectile->GetBoxComp()->IgnoreActorWhenMoving(this, true); 
	SpearProjectile->SetComponentsVisibility(false);
}

void ASpearman::HandlePlayerRevival()
{
	Super::HandlePlayerRevival(); 

	SpearProjectile->SetComponentsVisibility(false); 
}

void ASpearman::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage)
	{
		const TArray<FAnimNotifyEvent>& NotifyEvents = Montage->Notifies; 

		for (const FAnimNotifyEvent& NotifyEvent : NotifyEvents)
		{
			UAnimNotify* AnimNotify = NotifyEvent.Notify; 
			if (UAN_ThrowSpear* ThrowSpearNotify = Cast<UAN_ThrowSpear>(AnimNotify))
			{
				SpearProjectile->Destroy(); 
				/*ASpearWeapon* SpearWeapon = GetSpearWeapon(); 
				AAttachment* SpearAttachment = SpearWeapon->GetAttachment();
				SpearAttachment->SetActorHiddenInGame(false);*/

				TArray<AActor*> AttachedActors; 
				GetAttachedActors(AttachedActors); 
				for (AActor* AttachedActor : AttachedActors)
				{
					if (AAttachment* SpearAttachment = Cast<AAttachment>(AttachedActor))
					{
						SpearAttachment->SetActorHiddenInGame(false); 
					}
				}

				SetupSpearProjectile(); 
			}
		}
	}

	bCanThrowSpear = true; 
}

void ASpearman::ThrowSpear()
{
	SpearProjectile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FName SocketName = TEXT("Hand_Spear_R");

	if (!GetController()) return;
	const FRotator& SpearControlRotation = GetController()->GetControlRotation();
	const FVector& SpearControlVector = SpearControlRotation.Vector(); 

	SpearProjectile->SetActorRotation(SpearControlRotation - FRotator(0., 90., 0.)); 
	UProjectileMovementComponent* ProjectileComp = SpearProjectile->GetProjectileComp();
	ProjectileComp->Velocity = SpearControlVector * 1500.f;
	ProjectileComp->Activate(true);
	SpearProjectile->SetActorEnableCollision(true);
}
