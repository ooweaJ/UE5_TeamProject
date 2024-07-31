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
