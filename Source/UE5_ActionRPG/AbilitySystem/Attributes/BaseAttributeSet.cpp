// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/BaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Engine.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitHP(100.f);
	InitMaxHP(100.f);
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetBaseDamageAttribute())
	{
		const float LocalBaseDamage = GetBaseDamage();
		SetBaseDamage(0.f);

		if (LocalBaseDamage > 0.f)
		{
			const float NewHealth = GetHP() - LocalBaseDamage;
			SetHP(FMath::Clamp(NewHealth, 0.f, GetMaxHP()));
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Blue, FString::SanitizeFloat(GetHP()));
		}
	}

}
