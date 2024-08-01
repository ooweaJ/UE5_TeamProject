// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/Item.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UE5_ACTIONRPG_API ABaseWeapon : public AItem
{
	GENERATED_BODY()
	
public:
	ABaseWeapon();

	virtual void BeginPlay() override;

	FORCEINLINE void ReSetHitted() { HittedCharacters.Empty(); }

	UFUNCTION()
	void OnDamage(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter);
	virtual void OnDefaultAction();
	virtual void EndAction();
	virtual void ItemAction();
public:
	TArray<class ACharacter*> HittedCharacters;
	uint32 ComboCount = 1;
	float WeaponDamage = 100.f;
	float AttackSpeed = 1.f;
	bool bCanCombo;
	bool bSucceed;
};
