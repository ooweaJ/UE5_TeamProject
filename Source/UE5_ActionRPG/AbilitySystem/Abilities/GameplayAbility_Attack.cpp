#include "AbilitySystem/Abilities/GameplayAbility_Attack.h"
#include "Animation/AnimMontage.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Interface/CombatInterface.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UGameplayAbility_Attack::UGameplayAbility_Attack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGameplayAbility_Attack::ApplyGameplayEffectToActor()
{
	ICombatInterface* Source = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!Source) return;

	if (Source->GetTargetActor().IsEmpty()) return;

	Source->ApplyGamePlayEffectToTarget(Source->GetTargetActor(), GameplayEffectClass);
}

bool UGameplayAbility_Attack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}

	return true;
}

void UGameplayAbility_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (Montage)
	{
		ABasePlayer* Player = Cast<ABasePlayer>(ActorInfo->AvatarActor);
		Player->PlayAnimMontage(Montage);
	}
	//UAbilityTask_WaitGameplayEvent* WaitForEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EventTag);
	//WaitForEvent->EventReceived.AddDynamic(this, &ThisClass::ApplyGameplayEffectToActor);
	//WaitForEvent->ReadyForActivation();
}

void UGameplayAbility_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}
