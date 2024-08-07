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
	FORCEINLINE class AAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE FActionData* GetCurrentData() { return CurrentData; }

protected:
	virtual void BeginPlay() override;
	void AddActionData();

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual FActionData* GetDefaultAction(uint32 Num = 1);
	virtual FActionData* GetDefaultAction2(uint32 Num = 1);
	virtual FActionData* GetSkillAction(uint32 Num = 1);
	virtual FActionData* GetUltimateAction();

	virtual void OnDefaultAction();
	virtual void OnDefaultAction2();
	virtual void OnDefaultAction3();
	virtual void OnSkillAction();
	virtual void OnSkillAction2();
	virtual void OnSkillAction3();
	virtual void OnUltimateAction();

	virtual void OffDefaultAction();
	virtual void OffDefaultAction2();
	virtual void OffDefaultAction3();
	virtual void OffSkillAction();
	virtual void OffSkillAction2();
	virtual void OffSkillAction3();
	virtual void OffUltimateAction();

	void SetupItemData();

	virtual void EndAction();
	virtual void ItemAction();
	virtual void ItemAction2();
	virtual void OnItemSkillAction();
	virtual void OffItemSkillAction();

	void OnItemAction(int32 Num);

	void MontagePlayRate(UAnimInstance* AnimInstance, float PlayRate);
	virtual void OnItemSkillAction();
	virtual void OffItemSkillAction();
protected:
	UPROPERTY(EditAnywhere)
	class UCombatActionDataAsset* ItemData;

protected:
	class ACharacter* OwnerCharacter;
	class AAttachment* Attachment;
	class UStateComponent* OwnerState;
	class UStatusComponent* OwnerStatus;
	FItemInfoData* ItemInfoData;
	TMap<FGameplayTag, FActionData> ActionTagMap;
	FActionData* CurrentData;
};
