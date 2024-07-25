#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BasePlayer.generated.h"

UCLASS()
class UE5_ACTIONRPG_API ABasePlayer : public ACharacter, public IAbilitySystemInterface
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

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	virtual void InitAbilitySystem();

public:
	void OnAttack();

public:
	UPROPERTY(VisibleDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
	class UCameraComponent* Camera;

public:
	UPROPERTY(VisibleDefaultsOnly)
	class UStatusComponent* StatusComponent;

	UPROPERTY(VisibleDefaultsOnly)
	class UStateComponent* StateComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBaseAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBaseAttributeSet* AttributeSet;

	// Temp
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameplayEffect> Test;
};
