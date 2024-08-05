#include "Notifies/ANS_ItemSkill.h"
#include "Component/EquipComponent.h"
#include "Actor/Item/Weapon/BaseWeapon.h"
#include "Actor/Item/Attachment.h"

FString UANS_ItemSkill::GetNotifyName_Implementation() const
{
	return "ItemSkill";
}

void UANS_ItemSkill::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;

	if (ABaseWeapon* Weapon = Cast<ABaseWeapon>(Equip->GetCurrentItem()))
	{
		Weapon->OnItemSkillAction();
	}
}

void UANS_ItemSkill::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;

	if (ABaseWeapon* Weapon = Cast<ABaseWeapon>(Equip->GetCurrentItem()))
	{
		Weapon->OffItemSkillAction();
	}
}
