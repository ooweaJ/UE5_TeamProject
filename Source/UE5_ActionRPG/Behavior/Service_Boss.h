#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Service_Boss.generated.h"

UCLASS()
class UE5_ACTIONRPG_API UService_Boss : public UBTService
{
	GENERATED_BODY()
public:
	UService_Boss();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
