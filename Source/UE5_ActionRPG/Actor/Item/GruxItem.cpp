#include "Actor/Item/GruxItem.h"
#include "GameFramework/Character.h"
#include "Component/StateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actor/Character/AI/Grux.h"

AGruxItem::AGruxItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGruxItem::BeginPlay()
{
	Super::BeginPlay();

	if (AGrux* grux = Cast<AGrux>(GetOwner()))
	{
		Grux =  grux;
	}
}

void AGruxItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGruxItem::OnDefaultAction()
{
	Super::OnDefaultAction();
}

void AGruxItem::OnDefaultAction2()
{
	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;

		return;
	}
	if (!OwnerState->IsIdleMode()) return;

	FActionData* Data = GetDefaultAction2();
	if (!Data) return;

	OwnerCharacter->PlayAnimMontage(Data->AnimMontage);
	OwnerState->SetActionMode();
}

void AGruxItem::OnDefaultAction3()
{
	Super::OnDefaultAction3();
	OwnerState->SetActionMode();
}

void AGruxItem::OnSkillAction()
{
	if (!OwnerState) return;
	if (UCharacterMovementComponent* Movement = OwnerCharacter->GetCharacterMovement())
	{
		Movement->SetMovementMode(EMovementMode::MOVE_Flying);
		Super::OnSkillAction();
	}
}

void AGruxItem::OnSkillAction2()
{
	if (!OwnerState) return;
	if (!OwnerState->IsIdleMode())return;
	Super::OnSkillAction2();
	OwnerState->SetActionMode();
}

void AGruxItem::OnSkillAction3()
{
	if (!OwnerState) return;
	if (!OwnerState->IsIdleMode())return;
	Super::OnSkillAction3();
	OwnerState->SetActionMode();
}

void AGruxItem::OnUltimateAction()
{
	if (!OwnerState) return;
	if (!OwnerState->IsIdleMode())return;
	Super::OnUltimateAction();
	OwnerState->SetActionMode();
}

void AGruxItem::OffDefaultAction()
{
}

void AGruxItem::OffDefaultAction2()
{
}

void AGruxItem::OffDefaultAction3()
{
}

void AGruxItem::OffSkillAction()
{
}

void AGruxItem::OffSkillAction2()
{
}

void AGruxItem::OffSkillAction3()
{
}

void AGruxItem::OffUltimateAction()
{
}

void AGruxItem::OnItemSkillAction()
{
	Grux->OnFlySkill();
}

