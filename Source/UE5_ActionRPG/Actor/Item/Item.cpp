#include "Actor/Item/Item.h"
#include "GameFramework/Character.h"
#include "Actor/Item/Attachment.h"
#include "Data/ActionData/CombatActionDataAsset.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AItem::SetupItemData()
{
	if (ItemData)
	{
		ItemData->SetData(this);
		AddActionData();

		if (ItemInfoData)
		{
			{
				FTransform DefaultTransform;
				AAttachment* Actor = GetWorld()->SpawnActorDeferred<AAttachment>(ItemInfoData->Attachment, DefaultTransform, OwnerCharacter, OwnerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				Actor->SetOwnerCharacter(OwnerCharacter);
				Actor->FinishSpawning(DefaultTransform, true);
				Attachment = Actor;
				Attachment->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), ItemInfoData->SocketName);
			}
		}
	}
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	SetupItemData();
}

void AItem::AddActionData()
{
	TArray<FActionDataTableRow*> row;
	ItemInfoData->Data->GetAllRows<FActionDataTableRow>("", row);

	for (FActionDataTableRow* DataRow : row)
	{
		if (DataRow)
		{
			for (const FActionData& ActionData : DataRow->ActionDatas)
			{
				ActionTagMap.Add(ActionData.AbilityTag, ActionData);
			}
		}
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FActionData* AItem::GetDefaultAction(uint32 Num)
{
	FGameplayTag TargetTag = FGameplayTag::RequestGameplayTag(FName("Ability.Default." + FString::FromInt(Num)));

	if (FActionData* FoundData = ActionTagMap.Find(TargetTag))
	{
		return FoundData;
	}

	return nullptr;
}

FActionData* AItem::GetSkillAction(uint32 Num)
{
	FGameplayTag TargetTag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill." + FString::FromInt(Num)));

	if (FActionData* FoundData = ActionTagMap.Find(TargetTag))
	{
		return FoundData;
	}

	return nullptr;
}

FActionData* AItem::GetUltimateAction()
{
	FGameplayTag TargetTag = FGameplayTag::RequestGameplayTag(FName("Ability.Ultimate"));

	if (FActionData* FoundData = ActionTagMap.Find(TargetTag))
	{
		return FoundData;
	}

	return nullptr;
}

