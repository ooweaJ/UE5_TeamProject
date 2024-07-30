#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Actor/Item/Item.h"
#include "DataSubsystem.generated.h"

UCLASS()
class UE5_ACTIONRPG_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UDataSubsystem();

public:
	FORCEINLINE UDataTable* GetItemData() { return ItemDataTable; }

protected:
	UPROPERTY()
	UDataTable* ActionDataTable;

	UPROPERTY()
	UDataTable* ItemDataTable;
};
