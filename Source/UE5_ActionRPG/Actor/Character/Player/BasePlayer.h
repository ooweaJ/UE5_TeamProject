#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/BaseCharacter.h"
#include "BasePlayer.generated.h"

UCLASS()
class UE5_ACTIONRPG_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABasePlayer(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	void OnMouseL();
	void OnMouseR();
	void OffMouseL();
	void OffMouseR();
	void OnEvade();

	UFUNCTION(Server, Reliable)
	void ServerOnMouseL();
	void ServerOnMouseL_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnDefaultAction();
	void MulticastOnDefaultAction_Implementation();

	UFUNCTION(BlueprintCallable)
	void LockOn();
	
	void TickLockOn();
public:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly)
	FVector ForwardInput;

	UPROPERTY(BlueprintReadOnly)
	FVector RightInput;

	UPROPERTY(BlueprintReadOnly)
	FVector MoveDirection;
	
	UPROPERTY(BlueprintReadOnly)
	float WalkingDirectionAngle;

	UPROPERTY(BlueprintReadWrite)
	bool bLockOn = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool bEquipState;

	UPROPERTY(BlueprintReadWrite)
	float CharacterRotationAlphaLinearValue = 1;

	UPROPERTY(BlueprintReadWrite)
	float LeftHandWeight;

	UPROPERTY(BlueprintReadWrite)
	float UpperWeight;

	UPROPERTY(BlueprintReadWrite)
	AActor* TargetActor = nullptr;

	UPROPERTY(BlueprintReadWrite)
	float LockOnCameraArmLength = 300.0f;
	float LockOnRadius = 900;

	UPROPERTY(BlueprintReadWrite)
	float TESTNum = 0;

	bool Condition = true;
	
	FVector ArmPos;
	FVector ActorPos;

};
