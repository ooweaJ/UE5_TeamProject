#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "GameplayEffect.h"
#include "BaseCharacter.generated.h"

UCLASS()
class UE5_ACTIONRPG_API ABaseCharacter : public ACharacter , public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE void SetParrying(bool InParry) { Parrying = InParry; }
	FORCEINLINE bool GetParrying() { return Parrying; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	class UStatusComponent* GetStatus() const;
	
	void EndAction();
	void HitPlayMontage(TSubclassOf<UDamageType> InDamageType);
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItem> DefaultItemClass;

	UPROPERTY(EditAnywhere)
	class UMontageComponent* MontageComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStateComponent* State;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UEquipComponent* Equip;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStatusComponent* Status;

	bool Parrying;
};
