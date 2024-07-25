#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/BossAttributeSet.h"

AAIBaseCharacter::AAIBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UBossAttributeSet>(TEXT("AttributeSet"));
	{
		StatusComponent = CreateDefaultSubobject<UStatusComponent>("StatusComponent");
		StateComponent = CreateDefaultSubobject<UStateComponent>("StateComponent");
	}
}

void AAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilitySystem();
}

void AAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AAIBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAIBaseCharacter::InitAbilitySystem()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
