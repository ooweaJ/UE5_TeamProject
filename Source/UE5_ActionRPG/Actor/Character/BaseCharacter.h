#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "BaseCharacter.generated.h"

UCLASS()
class UE5_ACTIONRPG_API ABaseCharacter : public ACharacter ,public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void ApplyGamePlayEffectToTarget(TArray<AActor*> InTargetActor, TSubclassOf<UGameplayEffect> EffectClass);
	virtual TArray<AActor*> GetTargetActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAttachment> AttachmentClass;
	class AAttachment* Attachment;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBaseAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBaseAttributeSet* AttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStateComponent* State;
};
