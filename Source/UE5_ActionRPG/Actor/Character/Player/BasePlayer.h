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

public:
	void OnMouseL();
	void OnMouseR();
	void OffMouseL();
	void OffMouseR();

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
	bool bLockOn;
	
	UPROPERTY(BlueprintReadWrite)
	bool bEquipState;

	UPROPERTY(BlueprintReadWrite)
	float CharacterRotationAlphaLinearValue = 1;

	UPROPERTY(BlueprintReadWrite)
	float LeftHandWeight;

	UPROPERTY(BlueprintReadWrite)
	float UpperWeight;
};
