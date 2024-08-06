#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Grux.generated.h"

UCLASS()
class UE5_ACTIONRPG_API AGrux : public AAIBaseCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay();

public:
	virtual void Tick(float DeltaTime);

	void OnFlySkill();

	UFUNCTION()
	void SpawnActorsAround(float Distance, int32 NumberOfActors);

	FVector TarGetLocation;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AGruxMeteor> ActorToSpawn;

	UPROPERTY(BlueprintReadOnly)
	bool bFly = false;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;

};
