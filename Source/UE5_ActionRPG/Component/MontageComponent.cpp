#include "Component/MontageComponent.h"
#include "GameFramework/Character.h"
#include "Component/StatusComponent.h"

UMontageComponent::UMontageComponent()
{
}

void UMontageComponent::PlayKnockBack()
{
	PlayAnimMontage("KnockBack");
}

void UMontageComponent::PlayAvoid(FName SlotName)
{
	PlayAnimMontage("Avoid", SlotName);
}

void UMontageComponent::PlayRoll()
{
	PlayAnimMontage("Roll");
}

void UMontageComponent::PlayHit()
{
	PlayAnimMontage("Hit");
}

void UMontageComponent::PlayAnimMontage(FName Key, FName SlotName)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	if (!MontageData) return;
	FMontageData* data = MontageData->FindRow<FMontageData>(Key, "");
	if (!data) return;

	UStateComponent* state = character->GetComponentByClass<UStateComponent>();
	UStatusComponent* status = character->GetComponentByClass<UStatusComponent>();

	if (!data->AnimMontage) return;
	character->StopAnimMontage();
	state->ChangeType(data->Type);
	data->bCanMove ? status->SetMove() : status->SetStop();
	if(SlotName != "")
		character->PlayAnimMontage(data->AnimMontage, data->PlayRate, SlotName);
	else
		character->PlayAnimMontage(data->AnimMontage, data->PlayRate, data->StartSection);
}

