#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/BaseCharacter.h"
#include "AIBaseCharacter.generated.h"

UCLASS()
class UE5_ACTIONRPG_API AAIBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAIBaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable)
	virtual void OnMelee(uint32 Num = 1);

	UFUNCTION(NetMulticast, Reliable)
	virtual void MultiOnMelee(uint32 Num = 1);
	UFUNCTION(Server, Reliable)
	virtual void OnSkill(uint32 Num = 1);
	UFUNCTION(NetMulticast, Reliable)
	virtual void MultiOnSkill(uint32 Num = 1);

	virtual void OnUltimate();
	virtual void OffMelee();
	virtual void OffSkill();
	virtual void OffUltimate();

	void TargetRotation();
	void RotateToTarget();
	virtual void UpdateHP();
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	FORCEINLINE void SetMoveDirection(FVector InDirection) { Direction = InDirection; }
	FORCEINLINE void SetStrafe(bool InStrafe) { bStrafe = InStrafe; }
	FORCEINLINE void SetRotate(bool InRotate) { bRotate = InRotate; }

protected:
	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* HealthWidget;
	UPROPERTY(EditAnyWhere)
	TSubclassOf<UUserWidget> StatusWidgetClass;
protected:
	class ABaseAIController* BaseController;
	FVector Direction;
	bool bStrafe = false;
	bool bRotate = false;
	FVector TargetLocation;
};
