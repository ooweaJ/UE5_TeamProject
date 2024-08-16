#include "Notifies/AN_ItemAction.h"
#include "Component/EquipComponent.h"
#include "Actor/Item/Item.h"

FString UAN_ItemAction::GetNotifyName_Implementation() const
{
	return "ItemAction";
}

void UAN_ItemAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;
	UEquipComponent* Equip = Cast<UEquipComponent>(Owner->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	if (AItem* Item = Cast<AItem>(Equip->GetCurrentItem()))
	{
		Item->OnItemAction(Num);
	}
}
