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

public:
	ASpearman(const FObjectInitializer& ObjectInitializer); 

protected:
	virtual void OnConstruction(const FTransform& Transform) override; 

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


protected:
	class USceneCaptureComponent2D* SceneCaptureComponent2D = nullptr; 

	bool bCanCombo = false; 
	
};
