// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Spearman.generated.h"

class USceneCaptureComponent2D; 
class ASpearProjectile; 
class ASpearWeapon;

UCLASS()
class UE5_ACTIONRPG_API ASpearman : public ABasePlayer
{
	GENERATED_BODY()

public:
	ASpearman(const FObjectInitializer& ObjectInitializer); 

public:
	ASpearProjectile* GetSpearProjectile() const { return SpearProjectile; }
	ASpearWeapon* GetSpearWeapon() const;

	void ThrowSpear();

protected:
	virtual void OnConstruction(const FTransform& Transform) override; 

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void SetupSpearProjectile(); 


protected:
	UPROPERTY()
	USceneCaptureComponent2D* SceneCaptureComponent2D = nullptr; 

	UPROPERTY()
	ASpearProjectile* SpearProjectile = nullptr; 

	bool bCanCombo = false; 
	
};
