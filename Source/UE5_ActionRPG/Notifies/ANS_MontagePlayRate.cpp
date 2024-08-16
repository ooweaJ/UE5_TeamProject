#include "Notifies/ANS_MontagePlayRate.h"
#include "Component/EquipComponent.h"
#include "Actor/Item/Item.h"
#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Actor/Controller/AIController/BaseAIController.h"

FString UANS_MontagePlayRate::GetNotifyName_Implementation() const
{
	return "PlayRate";
}

void UANS_MontagePlayRate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp == nullptr) return;

	if (AAIBaseCharacter* Ai = Cast<AAIBaseCharacter>(MeshComp->GetOwner()))
	{
		if (ABaseAIController* Controller = Cast<ABaseAIController>(Ai->GetController()))
		{
			Controller->MontagePlayRate();
		}
	}

}

void UANS_MontagePlayRate::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;

	UEquipComponent* Equip = Cast<UEquipComponent>(MeshComp->GetOwner()->GetComponentByClass<UEquipComponent>());
	if (Equip == nullptr) return;
	if (AItem* Item = Cast<AItem>(Equip->GetCurrentItem()))
	{
		if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
		{
			Item->MontagePlayRate(AnimInstance, 1.0f);
		}
	}
}
