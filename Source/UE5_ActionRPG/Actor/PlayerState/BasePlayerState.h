// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BasePlayerState.generated.h"

class UPlayerAttributeSet;
class UBaseAbilitySystemComponent;

UCLASS()
class UE5_ACTIONRPG_API ABasePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ABasePlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UBaseAbilitySystemComponent* GetPlayerAbilitySystemComponent() const;
	UPlayerAttributeSet* GetPlayerSet() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBaseAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlayerAttributeSet* PlayerSet;
};
