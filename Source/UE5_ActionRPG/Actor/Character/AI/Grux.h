#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Grux.generated.h"

struct FActionData;

UCLASS()
class UE5_ACTIONRPG_API AGrux : public AAIBaseCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay();

public:
	virtual void Tick(float DeltaTime);

	void OnFlySkill(FActionData* InData);

	UFUNCTION()
	void SpawnActorsAround(float Distance, int32 NumberOfActors);

	UFUNCTION()
	void FinishFlySkill();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AGruxMeteor> ActorToSpawn;

	UPROPERTY(EditAnywhere)
	UAnimMontage* FlyAttack;

	UPROPERTY(BlueprintReadOnly)
	bool bFly = false;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
	FVector TarGetLocation;
	FActionData* Data;
};
