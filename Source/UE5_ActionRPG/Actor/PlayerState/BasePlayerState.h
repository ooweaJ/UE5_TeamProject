// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BasePlayerState.generated.h"

UCLASS()
class UE5_ACTIONRPG_API ABasePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ABasePlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
