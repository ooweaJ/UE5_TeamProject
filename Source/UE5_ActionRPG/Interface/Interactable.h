#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class UE5_ACTIONRPG_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void OnInteraction() = 0;
};
