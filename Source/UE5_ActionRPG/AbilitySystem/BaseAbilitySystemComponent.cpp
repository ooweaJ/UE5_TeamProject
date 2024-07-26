// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAbilitySystemComponent.h"

void UBaseAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities)
{
	for (auto& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		
		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);
		auto& a = ActivatableAbilities;
		SpecHandles.Add(SpecHandle);
	}
}

void UBaseAbilitySystemComponent::ActiveAbility(FGameplayTag AbilityTag)
{
	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		//TryActivateAbilitiesByTag();
		//TryActivateAbility(SpecHandle);
		// AbilitySpec을 가져옵니다.
		FGameplayTagContainer Tags = GetAbilityTags(SpecHandle);
		if (Tags.HasTag(AbilityTag))
		{
			TryActivateAbility(SpecHandle);
			break; // 첫 번째로 발견된 능력만 활성화하고 루프 종료
		}
	}
}

FGameplayAbilitySpec* UBaseAbilitySystemComponent::GetAbilitySpec(FGameplayAbilitySpecHandle Handle)
{
	// AbilitySpec을 찾기 위해 SpecHandles 배열을 탐색합니다.
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.Handle == Handle)
		{
			return const_cast<FGameplayAbilitySpec*>(&Spec);
		}
	}
	return nullptr; // 찾지 못한 경우 nullptr 반환
}

FGameplayTagContainer UBaseAbilitySystemComponent::GetAbilityTags(FGameplayAbilitySpecHandle SpecHandle)
{
	FGameplayAbilitySpec* AbilitySpec = GetAbilitySpec(SpecHandle);
	if (AbilitySpec && AbilitySpec->Ability)
	{
		return AbilitySpec->Ability->AbilityTags;
	}
	return FGameplayTagContainer(); // 태그가 없을 경우 빈 컨테이너 반환
}
