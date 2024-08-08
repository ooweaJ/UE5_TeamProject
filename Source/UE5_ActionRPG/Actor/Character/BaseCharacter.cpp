#include "Actor/Character/BaseCharacter.h"
#include "Actor/Item/Item.h"
#include "Component/StateComponent.h"
#include "Component/StatusComponent.h"
#include "Component/EquipComponent.h"
#include "Component/MontageComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Actor/Item/DamageType/DefaultDamageType.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	Equip = ObjectInitializer.CreateDefaultSubobject<UEquipComponent>(this, TEXT("EquipComponent"));
	State = ObjectInitializer.CreateDefaultSubobject<UStateComponent>(this, TEXT("StateComponent"));
	Status = ObjectInitializer.CreateDefaultSubobject<UStatusComponent>(this, TEXT("StatusComponent"));
	MontageComponent = ObjectInitializer.CreateDefaultSubobject<UMontageComponent>(this, TEXT("MontageComponent"));
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
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

void ABaseCharacter::EndAction()
{
	if (!State && !Equip) return;

	State->SetIdleMode();
	Equip->EndAction();
}

void ABaseCharacter::HitPlayMontage(TSubclassOf<UDamageType> InDamageType)
{

	if (UDefaultDamageType* DamageType = Cast<UDefaultDamageType>(InDamageType->GetDefaultObject()))
	{
		if (!MontageComponent) return;
		switch (DamageType->Type)
		{
		case EDamageType::Default:
			break;
		case EDamageType::Hitstop:
			MontageComponent->PlayHit();
			break;
		case EDamageType::Stun:
			MontageComponent->PlayStun();
			break;
		case EDamageType::Knockback:
			MontageComponent->PlayKnockBack();
			break;
		case EDamageType::Knockdown:
			break;
		}
	}
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!DamageEvent.DamageTypeClass) return 0;

	HitPlayMontage(DamageEvent.DamageTypeClass);

	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Blue, FString::SanitizeFloat(DamageAmount));

	Status->StatusModify(Status->HP, -DamageAmount);

	return DamageAmount;
}


