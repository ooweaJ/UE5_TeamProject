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

	void OnDamage(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter);

public:
	float WeaponDamage = 100.f;
	float AttackSpeed = 1.f;
};
