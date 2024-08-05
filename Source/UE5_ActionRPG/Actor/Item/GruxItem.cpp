#include "Actor/Item/GruxItem.h"
#include "GameFramework/Character.h"
#include "Component/StateComponent.h"

AGruxItem::AGruxItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGruxItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGruxItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGruxItem::OnDefaultAction()
{
	if (!OwnerState) return;
	if (!OwnerState->IsIdleMode())return;
	Super::OnDefaultAction();
	OwnerState->SetActionMode();
}

void AGruxItem::OnDefaultAction2()
{
	Super::OnDefaultAction2();
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
	Super::OnSkillAction();
	OwnerState->SetActionMode();
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

