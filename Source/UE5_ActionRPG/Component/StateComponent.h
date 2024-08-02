	#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Equip, Action, Hitted, Dead, Max, Dodge
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_ACTIONRPG_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }
	FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }
	FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }
	FORCEINLINE bool IsDodgeMode() { return Type == EStateType::Dodge; }
	FORCEINLINE EStateType GetCurrentMode() { return Type; }
	

public:
	void SetIdleMode();
	void SetEquipMode();
	void SetActionMode();
	void SetHittedMode();
	void SetDeadMode();
	void SetDodgeMode();
	void ChangeType(EStateType InNewType);

	void SetOnOrient();
	void SetOffOrient();

private:
	EStateType Type;
	class ACharacter* OwnerCharacter;
};
