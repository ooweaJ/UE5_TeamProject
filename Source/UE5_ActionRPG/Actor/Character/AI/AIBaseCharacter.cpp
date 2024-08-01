#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"


AAIBaseCharacter::AAIBaseCharacter(const FObjectInitializer& ObjectInitializer)
 : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Boss");
}

void AAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIBaseCharacter::OnMelee()
{
	if (!State) return;
		State->SetActionMode();
}

void AAIBaseCharacter::OnSkill()
{
	State->SetActionMode();
}

void AAIBaseCharacter::OnUltimate()
{
	State->SetActionMode();
}

void AAIBaseCharacter::OffMelee()
{
}

void AAIBaseCharacter::OffSkill()
{
}

void AAIBaseCharacter::OffUltimate()
{
}
