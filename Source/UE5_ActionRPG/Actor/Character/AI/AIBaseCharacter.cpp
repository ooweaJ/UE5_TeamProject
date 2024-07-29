#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/BossAttributeSet.h"

AAIBaseCharacter::AAIBaseCharacter(const FObjectInitializer& ObjectInitializer)
 : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	AttributeSet = CreateDefaultSubobject<UBossAttributeSet>(TEXT("AttributeSet"));
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
