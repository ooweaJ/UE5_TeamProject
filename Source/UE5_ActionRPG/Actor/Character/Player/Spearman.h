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
	ASpearman(const FObjectInitializer& ObjectInitializer); 

public:
	ASpearProjectile* GetSpearProjectile() const { return SpearProjectile; }
	ASpearWeapon* GetSpearWeapon() const;
	UCameraComponent* GetCamera() const { return Camera; }

	void ThrowSpear();

protected:
	virtual void OnConstruction(const FTransform& Transform) override; 

	virtual void BeginPlay() override; 

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void SetupSpearProjectile(); 


protected:
	UPROPERTY(EditAnywhere)
	ASpearProjectile* SpearProjectile = nullptr; 

	bool bCanCombo = false; 

private:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted); 
	
};
