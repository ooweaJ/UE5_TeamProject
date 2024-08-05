// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/SpearProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ASpearProjectile::ASpearProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
		SetRootComponent(Box);
		Box->SetBoxExtent(FVector(180., 430., 180.)); 
	}

	{
		SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh")); 
		SkeletalMesh->SetupAttachment(GetRootComponent()); 

		static ConstructorHelpers::FObjectFinder<USkeletalMeshComponent> SkeletalAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Boss/Boss_Asset/InfinityBladeWeapons/Weapons/Spear/source/SpearofAdun.SpearofAdun'"));
		ensure(SkeletalAsset.Object); 
		SkeletalMesh = SkeletalAsset.Object; 
	}

	{
		ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
		ProjectileComp->InitialSpeed = 1000.f;
		ProjectileComp->bRotationFollowsVelocity = false;
		ProjectileComp->ProjectileGravityScale = 0.f;
		ProjectileComp->bShouldBounce = false;
	}

	//if (bCanCombo)
//{
//	AActor* SpearOwner = GetOwner();
//	if (ABasePlayer* SpearPlayer = Cast<ABasePlayer>(SpearOwner))
//	{
//		SpearPlayer->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

//		const FTransform& SpearTransform = SpearPlayer->GetMesh()->GetSocketTransform(TEXT("Hand_Spear_R"), ERelativeTransformSpace::RTS_ParentBoneSpace); 
//		const FVector& SpearLocation = SpearTransform.GetLocation(); 
//		const FRotator& SpearRotation = SpearTransform.GetRotation().Rotator();

//		const FVector SpearForwardVector = UKismetMathLibrary::GetForwardVector(SpearRotation) * 3000.f; 
//		ProjectileComp->SetVelocityInLocalSpace(SpearForwardVector); 
//		ProjectileComp->Activate(); 
//		SetActorEnableCollision(true); 
//	}
//}
}

