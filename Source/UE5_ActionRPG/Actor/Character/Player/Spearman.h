// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Spearman.generated.h"

class USceneCaptureComponent2D; 
class ASpearProjectile; 
class ASpearWeapon;
class UCameraComponent; 

UCLASS()
class UE5_ACTIONRPG_API ASpearman : public ABasePlayer
{
	GENERATED_BODY()

public:
	ASpearman(); 

public:
	ASpearProjectile* GetSpearProjectile() const { return SpearProjectile; }
	ASpearWeapon* GetSpearWeapon() const;
	UCameraComponent* GetCamera() const { return Camera; }

	void ThrowSpear();

	bool bCanThrowSpear = false; 

protected:
	virtual void OnConstruction(const FTransform& Transform) override; 

	virtual void BeginPlay() override; 

	void SetupSpearProjectile(); 


protected:
	UPROPERTY(EditAnywhere)
	ASpearProjectile* SpearProjectile = nullptr; 

	bool bCanCombo = false; 

private:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted); 	
};
