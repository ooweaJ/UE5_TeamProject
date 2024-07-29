#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CombatActionDataAsset.generated.h"


class UGameplayAbility;

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> Abiilty = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString AbilityName = FString();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Abilityescription = FString();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AbilityCooldownTime = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AbilityPower = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AbilityDuration = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AbilityDurationPower = 0.0f;
};


UCLASS()
class UE5_ACTIONRPG_API UCombatActionDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAbilityInfo> AbilityInformation;

	FAbilityInfo FindAbilityInfoForTag(const FGameplayTag& AbilityTag) const;
	TSubclassOf<UGameplayAbility> FindAbilityForTag(const FGameplayTag& AbilityTag) const;
};
