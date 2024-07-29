#include "Data/ActionData/CombatActionDataAsset.h"
#include "Abilities/GameplayAbility.h"

FAbilityInfo UCombatActionDataAsset::FindAbilityInfoForTag(const FGameplayTag& AbilityTag) const
{
	for (const auto& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	return FAbilityInfo();
}

TSubclassOf<UGameplayAbility> UCombatActionDataAsset::FindAbilityForTag(const FGameplayTag& AbilityTag) const
{
	for (const auto& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info.Abiilty;
		}
	}
	return nullptr;
}
