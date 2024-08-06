#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/StateComponent.h"
#include "MontageComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
	EStateType Type = EStateType::Action;
	
	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_ACTIONRPG_API UMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMontageComponent();

	void PlayKnockBack();
	void PlayAvoid(FName SlotName);
	void PlayRoll();
	void PlayHit();
	void PlayStun();

private:
	void PlayAnimMontage(FName Key, FName SlotName = "");

private:
	UPROPERTY(EditAnywhere)
	UDataTable* MontageData;
};
