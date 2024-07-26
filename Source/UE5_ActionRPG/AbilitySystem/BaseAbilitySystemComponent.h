#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class UE5_ACTIONRPG_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities);
	void ActiveAbility(FGameplayTag AbilityTag);
	FGameplayAbilitySpec* GetAbilitySpec(FGameplayAbilitySpecHandle Handle);
	FGameplayTagContainer GetAbilityTags(FGameplayAbilitySpecHandle SpecHandle);

	TArray<FGameplayAbilitySpecHandle> SpecHandles;
};
