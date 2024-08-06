#include "Actor/ProJectile/GruxMeteor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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
}

void AGruxMeteor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGruxMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGruxMeteor::OnTarget(uint32 num)
{
	if (!Target) return;
	FVector TargetDirection = Target->GetActorLocation() - GetActorLocation();

	Projectile->Velocity = TargetDirection * 3;

	float Delay = num * 0.5f;
	UKismetSystemLibrary::K2_SetTimer(this, "Activate", Delay, false);
}

void AGruxMeteor::Activate()
{
	Projectile->Activate();
}
