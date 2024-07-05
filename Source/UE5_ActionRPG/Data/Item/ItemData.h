#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon, Max
};


USTRUCT()
struct UE5_ACTIONRPG_API FItemData : public FTableRowBase
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere)
	FName ItemName;

	UPROPERTY(EditAnywhere)
	uint32 CurrentBundleCount = 0;

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere)
	FText ItemDesc;

	UPROPERTY(EditAnywhere)
	uint32 MaxBundleCount = 1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItem> ItemClass;
};
