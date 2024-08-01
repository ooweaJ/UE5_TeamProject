#include "Notifies/ANS_Combo.h"
#include "Component/EquipComponent.h"
#include "Actor/Item/Weapon/BaseWeapon.h"

FString UANS_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UANS_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	if (ABaseWeapon* Weapon = Cast<ABaseWeapon>(Equip->GetCurrentItem()))
	{
		Weapon->bCanCombo = true;
	}
}

void UANS_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	if (ABaseWeapon* Weapon = Cast<ABaseWeapon>(Equip->GetCurrentItem()))
	{
		Weapon->bCanCombo = false;
	}
}
