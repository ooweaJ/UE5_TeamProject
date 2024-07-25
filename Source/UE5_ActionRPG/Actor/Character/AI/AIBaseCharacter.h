#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AIBaseCharacter.generated.h"

UCLASS()
class UE5_ACTIONRPG_API AAIBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAIBaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	virtual void InitAbilitySystem();

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
};
