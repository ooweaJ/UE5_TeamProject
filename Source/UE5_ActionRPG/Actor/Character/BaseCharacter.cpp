#include "Actor/Character/BaseCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Actor/Item/Item.h"
#include "Component/StateComponent.h"
#include "Component/EquipComponent.h"


ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UBaseAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	Equip = ObjectInitializer.CreateDefaultSubobject<UEquipComponent>(this, TEXT("EquipComponent"));
	State = ObjectInitializer.CreateDefaultSubobject<UStateComponent>(this, TEXT("StateComponent"));

	NetUpdateFrequency = 100.0f;

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultItemClass)
	{
		FTransform DefaultTransform;
		FActorSpawnParameters ASP;
		ASP.Owner = this;
		ASP.Instigator = this;
		ASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AItem* Item = GetWorld()->SpawnActor<AItem>(DefaultItemClass, DefaultTransform,ASP);
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

void ABaseCharacter::ApplyGamePlayEffectToTarget(TArray<AActor*> InTargetActor, TSubclassOf<UGameplayEffect> EffectClass)
{
	if (InTargetActor.IsEmpty()) return;

	for (auto& Target : InTargetActor)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponent();

		FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
		ContextHandle.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(EffectClass, 1.f, ContextHandle);

		if (Target && IsValid(Target) && TargetASC)
			SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
	}
}

TArray<AActor*> ABaseCharacter::GetTargetActor()
{
	return TArray<AActor*>();
}
