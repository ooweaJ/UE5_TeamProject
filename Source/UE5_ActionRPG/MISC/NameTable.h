#pragma once

#include "CoreMinimal.h"

struct UE5_ACTIONRPG_API FBlackBoardKeyNameTable
{
	static inline FName TargetKey = TEXT("Target");
	static inline FName LocationKey = TEXT("Location");

};

struct UE5_ACTIONRPG_API FCollisionPresetNameTable
{
	static inline FName PhysicsActor = TEXT("PhysicsActor");
	static inline FName Player = TEXT("Player");
	static inline FName PlayerDetect = TEXT("PlayerDetect");
	static inline FName PlayerProjectile = TEXT("PlayerProjectile");
	static inline FName Enemy = TEXT("Enemy");
};