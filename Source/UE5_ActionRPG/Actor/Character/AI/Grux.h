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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void SpawnActorsAround(float Distance, int32 NumberOfActors);

	UFUNCTION(Server,Reliable)
	void FinishFlySkill();
	UFUNCTION(NetMulticast,Reliable)
	void MultiFinishFlySkill();

	UFUNCTION()
	void OnUIPopUP(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AGruxMeteor> ActorToSpawn;

	UPROPERTY(EditAnywhere)
	UAnimMontage* FlyAttack;

	UPROPERTY(Replicated,BlueprintReadOnly)
	bool bFly = false;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
	FVector TarGetLocation;
	FActionData* Data;
};
