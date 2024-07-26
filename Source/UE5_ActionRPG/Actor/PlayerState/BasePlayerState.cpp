// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PlayerState/BasePlayerState.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/PlayerAttributeSet.h"

ABasePlayerState::ABasePlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PlayerSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerSet"));

}

UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBaseAbilitySystemComponent* ABasePlayerState::GetPlayerAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UPlayerAttributeSet* ABasePlayerState::GetPlayerSet() const
{
	return PlayerSet;
}
