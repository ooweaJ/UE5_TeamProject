#include "Actor/Character/BaseCharacter.h"
#include "Actor/Item/Item.h"
#include "Component/StateComponent.h"
#include "Component/EquipComponent.h"
#include "Component/StatusComponent.h"


ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	Equip = ObjectInitializer.CreateDefaultSubobject<UEquipComponent>(this, TEXT("EquipComponent"));
	State = ObjectInitializer.CreateDefaultSubobject<UStateComponent>(this, TEXT("StateComponent"));
}


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultItemClass)
	{
		FTransform DefaultTransform;
		AItem* Item = GetWorld()->SpawnActorDeferred<AItem>(DefaultItemClass, DefaultTransform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Item->SetOwnerCharacter(this);
		Item->FinishSpawning(DefaultTransform, true);
		Equip->SetSelectItem(Item);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

UStatusComponent* ABaseCharacter::GetStatusComponent() const
{
	return StatusComponent;
}
