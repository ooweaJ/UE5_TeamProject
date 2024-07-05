#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataSubsystem.generated.h"

UCLASS()
class UE5_ACTIONRPG_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UDataSubsystem();

protected:
	UPROPERTY()
	UDataTable* ActionDataTable;

	UPROPERTY()
	UDataTable* ItemDataTable;
};
