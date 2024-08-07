#include "Actor/ProJectile/GruxMeteor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/DamageEvents.h"

AGruxMeteor::AGruxMeteor()
{
	PrimaryActorTick.bCanEverTick = true;

	{
		Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
		SetRootComponent(Sphere);
		Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	}

	Projectile->InitialSpeed = 3000.f;
	Projectile->MaxSpeed = 3000.f;
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->bSweepCollision = true;
	Projectile->bAutoActivate = false;

	InitialLifeSpan = 7.f;
}

void AGruxMeteor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void AGruxMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGruxMeteor::OnTarget(uint32 num)
{
	float Delay = num * 0.5f;
	UKismetSystemLibrary::K2_SetTimer(this, "Activate", Delay, false);
}

void AGruxMeteor::Activate()
{
	if (!Target) return;
	FVector TargetDirection = Target->GetActorLocation() - GetActorLocation();

	Projectile->Velocity = TargetDirection * 20;
	Projectile->Activate();
}

void AGruxMeteor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ImpactParticle)
	{
		FVector location = Hit.Location;
		FRotator Rotation = Projectile->Velocity.GetSafeNormal().Rotation();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactParticle, location, Rotation);

		{
			TArray<FHitResult> HitResults;
			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
			if(UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), location, location, 300.f, ObjectTypes, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResults, true))
			{
				for (const FHitResult& Hit : HitResults)
				{
					AActor* HitActor = Hit.GetActor();
					if (HitActor->ActorHasTag("Player"))
					{
						//Damage
						float LocalDamage = Data->Power;
						LocalDamage = LocalDamage * FMath::FRandRange(0.9f, 1.1f);

						FDamageEvent de;
						de.DamageTypeClass = Data->DamageType;
						HitActor->TakeDamage(LocalDamage, de, GetOwner()->GetInstigatorController(), this);
					}
				}
			}
		}
	}
	Destroy();
}
