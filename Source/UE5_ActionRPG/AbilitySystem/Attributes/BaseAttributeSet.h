// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)			\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)	\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)				\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)				\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class UE5_ACTIONRPG_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
public:
	ATTRIBUTE_ACCESSORS(ThisClass, HP);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHP);
	ATTRIBUTE_ACCESSORS(ThisClass, MP);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMP);
	ATTRIBUTE_ACCESSORS(ThisClass, BaseDamage);

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData HP;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHP;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MP;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMP;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData BaseDamage;
};
