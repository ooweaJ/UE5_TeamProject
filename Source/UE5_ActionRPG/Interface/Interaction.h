#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UInteraction : public UInterface
{
	GENERATED_BODY()
};

class UE5_ACTIONRPG_API IInteraction
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Interaction() = 0;
};
