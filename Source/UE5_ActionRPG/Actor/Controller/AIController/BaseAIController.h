#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

UCLASS()
class UE5_ACTIONRPG_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	FORCEINLINE	void SetAttackRange(float Range) { AttackRange = Range; }
	FORCEINLINE float GetAttackRange() { return AttackRange; }
	FORCEINLINE class UBehaviorComponent* GetBehavior() { return Behavior; }

public:
	void SetLoactionKey(FVector InLoaction);
	void SetTargetKey(class ACharacter* InCharacter);

private:
	UPROPERTY(VisibleDefaultsOnly)
	class UBehaviorComponent* Behavior;
	UPROPERTY(VisibleDefaultsOnly)
	class UAIPerceptionComponent* Perception;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;

private:
	class AAIBaseCharacter* OwnerAI;
	class UAISenseConfig_Sight* Sight;
	float AttackRange = 100.f;
};
