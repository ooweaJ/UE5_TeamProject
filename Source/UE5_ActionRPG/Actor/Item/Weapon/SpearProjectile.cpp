// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/SpearProjectile.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASpearProjectile::ASpearProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Box Collision
	{
		Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
		SetRootComponent(Box);
		Box->SetBoxExtent(FVector(180., 430., 180.)); 
	}

	// Skeletal Mesh
	{
		SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh")); 
		SkeletalMesh->SetupAttachment(GetRootComponent()); 

		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Boss/Boss_Asset/InfinityBladeWeapons/Weapons/Spear/source/SpearofAdun.SpearofAdun'"));
		ensure(SkeletalAsset.Object); 
		SkeletalMesh->SetSkeletalMesh(SkeletalAsset.Object); 
	}

	// Niagara System Component
	{
		NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent")); 
		NiagaraComponent->SetupAttachment(SkeletalMesh); 

		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/_dev/Effect/Spear/Niagara/NS_SparkAura.NS_SparkAura'"));
		ensure(NiagaraAsset.Object); 
		NiagaraComponent->SetAsset(NiagaraAsset.Object); 
	}

	// Projectile Movement Component
	{
		ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
		ProjectileComp->InitialSpeed = 3000.f;
		/*ProjectileComp->MaxSpeed = 3000.f;
		ProjectileComp->bAutoActivate = false;*/
		ProjectileComp->ProjectileGravityScale = 0.f; 
	}

}

void ASpearProjectile::SetComponentsVisibility(bool bVisible)
{
	TArray<UActorComponent*> Components; 
	GetComponents(Components); 

	for (UActorComponent* Component : Components)
	{
		if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component))
		{
			PrimitiveComponent->SetVisibility(bVisible, true); 
		}
	}
}

void ASpearProjectile::BeginPlay()
{
	Super::BeginPlay(); 

	Box->OnComponentHit.AddDynamic(this, &ASpearProjectile::OnHit);

}

void ASpearProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		AAIBaseCharacter* BossCharacter = Cast<AAIBaseCharacter>(OtherActor); 

		if (!BossCharacter) { return;  }

		UGameplayStatics::ApplyDamage(BossCharacter, SpearThrowingDamage, nullptr, this, UDamageType::StaticClass()); 
		
	}
}