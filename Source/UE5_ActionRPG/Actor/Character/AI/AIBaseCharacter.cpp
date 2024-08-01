#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"
#include "Component/EquipComponent.h"
#include "Actor/Item/Item.h"

AAIBaseCharacter::AAIBaseCharacter(const FObjectInitializer& ObjectInitializer)
 : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Boss");
}

void AAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStrafe)
	{
		if (Status->IsCanMove())
		{
			if (Direction != FVector::ZeroVector)
			{
				AddMovementInput(Direction);
			}
		}
	}
}

void AAIBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIBaseCharacter::OnMelee(uint32 Num)
{
	if (!State && !Equip) return;
	if (!State->IsIdleMode()) return;
	
	if (AItem* Item = Equip->GetCurrentItem())
	{
		switch (Num)
		{
			case 1:
			{
				Item->OnDefaultAction();
				break;
			}
			case 2:
			{
				Item->OnDefaultAction2();
				break;
			}
			case 3:
			{
				Item->OnDefaultAction3();
				break;
			}
		}
	}
}

void AAIBaseCharacter::OnSkill(uint32 Num)
{
	if (!State && !Equip) return;
	State->SetActionMode();
	if (AItem* Item = Equip->GetCurrentItem())
	{
		switch (Num)
		{
		case 1:
		{
			Item->OnSkillAction();
			break;
		}
		case 2:
		{
			Item->OnSkillAction2();
			break;
		}
		case 3:
		{
			Item->OnSkillAction3();
			break;
		}
		}
	}
}

void AAIBaseCharacter::OnUltimate()
{
	if (!State && !Equip) return;
	State->SetActionMode();
	if (AItem* Item = Equip->GetCurrentItem())
		Item->OnUltimateAction();
}

void AAIBaseCharacter::OffMelee()
{
}

void AAIBaseCharacter::OffSkill()
{
}

void AAIBaseCharacter::OffUltimate()
{
}
