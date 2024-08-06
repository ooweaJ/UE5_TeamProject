// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpearProjectile.generated.h"


class UBoxComponent;
class USkeletalMeshComponent; 
class UProjectileMovementComponent;

UCLASS()
class UE5_ACTIONRPG_API ASpearProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpearProjectile();

public:
	void SetComponentsVisibility(bool bVisible);

	UProjectileMovementComponent* GetProjectileComp() const { return ProjectileComp; }

protected:
	virtual void BeginPlay() override; 

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
	float SpearThrowingDamage = 10.f; 
protected:
	UPROPERTY()
	UBoxComponent* Box; 

	UPROPERTY()
	USkeletalMeshComponent* SkeletalMesh; 

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileComp;
};
