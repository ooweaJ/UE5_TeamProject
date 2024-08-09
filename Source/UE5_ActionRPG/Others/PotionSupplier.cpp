// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/PotionSupplier.h"
#include "Components/SphereComponent.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/InGameHUD.h"

// Sets default values
APotionSupplier::APotionSupplier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
}

void APotionSupplier::Interaction()
{
	
}

// Called when the game starts or when spawned
void APotionSupplier::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APotionSupplier::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &APotionSupplier::OnEndOverlap);
}

// Called every frame
void APotionSupplier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APotionSupplier::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (ABasePlayer* BasePlayer = Cast<ABasePlayer>(OtherActor))
	{
		InteractionActor = OtherActor;
		BasePlayer->InteractableObject = this;
		AHUD* HUD = UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD();
		AInGameHUD* InGameHUD = Cast<AInGameHUD>(HUD);
	}
	
}

void APotionSupplier::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

