#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/BaseCharacter.h"
#include "BasePlayer.generated.h"

UCLASS()
class UE5_ACTIONRPG_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABasePlayer();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	void OnMouseL();
	UFUNCTION(Server, Reliable)
	void OnMouseR();
	UFUNCTION(NetMulticast, Reliable)
	void MultiOnMouseR();
	void OffMouseL();
	void OffMouseR();
	void OnQ(); 
	UFUNCTION(Server, Reliable)
	void OnShift();
	UFUNCTION(Server, Reliable)
	void OffShift();
	void OnEvade();
	void OnStepBack();
	void OnInteraction();
	void UsePotion();

	UFUNCTION(Server, Reliable)
	void ServerOnMouseL();
	void ServerOnMouseL_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnDefaultAction();
	void MulticastOnDefaultAction_Implementation();

	UFUNCTION(BlueprintCallable)
	void LockOn();
	
	void TickLockOn();
	virtual void UpdateHP();

	void SetPrimitiveComponentsVisibility(bool bVisible); 

	void SetAttachedActorsVisiblity(bool bVisible); 

	void DestroyAttachedActors(); 

	UFUNCTION(BlueprintCallable)
	void SetAirbone(bool InAirBone);

public:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly)
	float ForwardInput;

	UPROPERTY(BlueprintReadOnly)
	float RightInput;

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

	UPROPERTY(BlueprintReadOnly,Replicated)
	bool bAirBone;


	bool Condition = true;
	
	FVector ArmPos;
	FVector ActorPos;

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class AInteractiveActor* InteractableObject;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* DeathDissolveEffect; 
};
