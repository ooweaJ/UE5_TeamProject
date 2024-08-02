#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

UENUM(BlueprintType)
enum class EWalkSpeedTpye : uint8
{
	Sneak, Walk, Run, HighRun, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_ACTIONRPG_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE float GetSneakSpeed() { return Speed[(int32)EWalkSpeedTpye::Sneak]; }
	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)EWalkSpeedTpye::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)EWalkSpeedTpye::Run]; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE float GetMaxStamina() { return MaxStamina; }
	FORCEINLINE float GetStamina() { return Stamina; }
	FORCEINLINE float GetStaminaRegen() { return StaminaRegen; }
	FORCEINLINE float GetDodgeCost() { return DodgeCost; }
	FORCEINLINE float GetDamage() { return Damage; }
	// 캐릭터 이동 제어를 위해 받아옴
	FORCEINLINE bool IsCanMove() { return bCanMove; }

public:
	// 이동제어
	FORCEINLINE void SetMove() { bCanMove = true; }
	FORCEINLINE void SetStop() { bCanMove = false; }
	// 원하는 스피드 값 설정
	void SetSpeed(EWalkSpeedTpye InType);
	// 체력 증가 및 감소
	void IncreaseHealth(float InAmount);
	void DecreaseHealth(float InAmount);
	void SetDamage(float InAmount);
	// 마나 증가 및 감소
	void IncreaseMans(float InAmount);
	void DecreaseMana(float InAmount);
	// 스테미나 증가 및 감소
	void IncreaseStamina(float InAmount);
	void DecreaseStamina(float InAmount);
	void SetStaminaRegen(float InAmount);
	// 퍼센티지
	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();
	UFUNCTION(BlueprintCallable)
	float GetManaPercent();
	UFUNCTION(BlueprintCallable)
	float GetStaminaPercent();

private:
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Mana")
	float MaxMana = 100.f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaRegen = 1.f;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed[(int32)EWalkSpeedTpye::Max] = { 200, 300, 900, 1200 };

private:
	float Health;
	float Mana;
	float Stamina;
	float DodgeCost = 25.f;
	float Damage;
	bool bCanMove = true;
};
