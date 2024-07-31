#include "Actor/Item/WarriorItem.h"
#include "Actor/Character/Player/BasePlayer.h"

void AWarriorItem::OnDefaultAction()
{
	Super::OnDefaultAction();
}

void AWarriorItem::OnDefaultAction2()
{
}

void AWarriorItem::OnDefaultAction3()
{
}

void AWarriorItem::OnSkillAction()
{
	if (OwnerCharacter)
	{
		if (ABasePlayer* Player = Cast<ABasePlayer>(OwnerCharacter))
		{
			Player->UpperWeight = 1;
		}
	}
}

void AWarriorItem::OnSkillAction2()
{
}

void AWarriorItem::OnSkillAction3()
{
}

void AWarriorItem::OnUltimateAction()
{
}

void AWarriorItem::OffDefaultAction()
{

}

void AWarriorItem::OffDefaultAction2()
{
}

void AWarriorItem::OffDefaultAction3()
{
}

void AWarriorItem::OffSkillAction()
{
	if (OwnerCharacter)
	{
		if (ABasePlayer* Player = Cast<ABasePlayer>(OwnerCharacter))
		{
			Player->UpperWeight = 0;
		}
	}
}

void AWarriorItem::OffSkillAction2()
{
}

void AWarriorItem::OffSkillAction3()
{
}

void AWarriorItem::OffUltimateAction()
{
}
