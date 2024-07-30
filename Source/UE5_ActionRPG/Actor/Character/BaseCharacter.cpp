#include "Actor/Character/BaseCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Actor/Item/Attachment.h"
#include "Component/StateComponent.h"
#include "Component/StatusComponent.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UBaseAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

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

	if (AttachmentClass)
	{
		FTransform DefaultTransform;
		AAttachment* Actor = GetWorld()->SpawnActorDeferred<AAttachment>(AttachmentClass, DefaultTransform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Actor->SetOwnerCharacter(this);
		Actor->FinishSpawning(DefaultTransform, true);
		Attachment = Actor;
		Attachment->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), FName("Hand_R"));
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
	return Attachment->GetTargets();
}

UStatusComponent* ABaseCharacter::GetStatusComponent()
{
	return StatusComponent;
}
