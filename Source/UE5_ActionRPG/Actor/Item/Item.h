#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ActionData/ActionDataTableRow.h"
#include "GameplayTagContainer.h"
#include "Item.generated.h"

struct FActionData;
struct FItemInfoData;
struct FGameplayTag;

UCLASS()
class UE5_ACTIONRPG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	FORCEINLINE void SetItemInfoData(FItemInfoData* InData) { ItemInfoData = InData; }
	FORCEINLINE void SetOwnerCharacter(ACharacter* InCharacter) { OwnerCharacter = InCharacter; }

protected:
	virtual void BeginPlay() override;
	void AddActionData();

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual FActionData* GetDefaultAction(uint32 Num = 1);
	virtual FActionData* GetSkillAction(uint32 Num = 1);
	virtual FActionData* GetUltimateAction();

	virtual void OnDefaultAction();
	virtual void OnSkillAction();

	void SetupItemData();

protected:
	UPROPERTY(EditAnywhere)
	class UCombatActionDataAsset* ItemData;

protected:
	class ACharacter* OwnerCharacter;
	class AAttachment* Attachment;
	FItemInfoData* ItemInfoData;

	TMap<FGameplayTag, FActionData> ActionTagMap;
};
