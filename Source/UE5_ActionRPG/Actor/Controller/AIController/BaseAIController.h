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
	FORCEINLINE bool IsOnSkill() { return bSkill; }
	FORCEINLINE bool IsOnUltimate() { return bUltimate; }

public:
	void SetLoactionKey(FVector InLoaction);
	void SetTargetKey(class ACharacter* InCharacter);

	virtual void OnMeleeAttack();
	virtual void OnSkill();
	virtual void OnUltimate();

	class ACharacter* GetTarget();
protected:
	UPROPERTY(EditAnywhere)
	class UBehaviorComponent* Behavior;
	UPROPERTY(EditAnywhere)
	class UAIPerceptionComponent* Perception;

protected:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

protected:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BTAsset;
	UPROPERTY(EditAnywhere)
	class UBlackboardData* BBAsset;
	UPROPERTY(EditAnywhere)
	float SightRadius = 3000.f;

	UPROPERTY(EditAnywhere)
	float AttackRange = 150.f;
protected:
	class AAIBaseCharacter* OwnerAI;
	class UAISenseConfig_Sight* Sight;

	bool bSkill = false;
	bool bUltimate = false;
};
