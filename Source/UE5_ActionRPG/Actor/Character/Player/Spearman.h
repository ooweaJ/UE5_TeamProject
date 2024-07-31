// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Spearman.generated.h"

/**
 * 
 */
UCLASS()
class UE5_ACTIONRPG_API ASpearman : public ABasePlayer
{
	GENERATED_BODY()

protected:
	virtual void OnConstruction(const FTransform& Transform) override; 
	
};
