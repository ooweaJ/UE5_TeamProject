#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ActionData/ActionDataTableRow.h"
#include "Item.generated.h"

USTRUCT()
struct UE5_ACTIONRPG_API FItemActionData : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	UDataTable* Data;

	UPROPERTY(EditAnywhere, category = "Attach")
	TSubclassOf<class AAttachment> Attachment;

	UPROPERTY(EditAnywhere, category = "Attach")
	FName SocketName;

	UPROPERTY(EditAnywhere)
	EItemType ItemType;

	UPROPERTY(EditAnywhere)
	FEquipmentData Equip;
};

UCLASS()
class UE5_ACTIONRPG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetItemData(class ACharacter* InOnwerCharacter, const FItemActionData* InData);

protected:
	struct FActionDataTableRow* DefaultData;
	class ACharacter* OwnerCharacter;
	const FItemActionData* ActionData;
	class AAttachment* Attachment;

	UPROPERTY(EditAnywhere)
	EItemType ItemType;
private:

};
