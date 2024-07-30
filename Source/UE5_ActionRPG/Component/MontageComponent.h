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
	EStateType Type;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;

	UPROPERTY(EditAnywhere)
	bool bCanMove;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_ACTIONRPG_API UMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMontageComponent();

	void PlayKnockBack();
	void PlayAvoid();
	void PlayRoll();
	void PlayHit();

private:
	void PlayAnimMontage(FName Key);

private:
	UPROPERTY(EditAnywhere)
	UDataTable* MotageData;
};
