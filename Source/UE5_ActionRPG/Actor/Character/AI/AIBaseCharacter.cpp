#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"
#include "Component/EquipComponent.h"
#include "Actor/Item/Item.h"
#include "Actor/Controller/AIController/BaseAIController.h"
#include "Kismet/KismetMathLibrary.h"

AAIBaseCharacter::AAIBaseCharacter(const FObjectInitializer& ObjectInitializer)
 : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Boss");
}

void AAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ABaseAIController* controller = Cast<ABaseAIController>(GetController()))
	{
		BaseController = controller;
	}
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

	if (bRotate)
	{
		TargetRotation();
	}
}

void AAIBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIBaseCharacter::OnMelee_Implementation(uint32 Num)
{
	MultiOnMelee(Num);
}

void AAIBaseCharacter::MultiOnMelee_Implementation(uint32 Num)
{
	if (!State && !Equip) return;

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

void AAIBaseCharacter::OnSkill_Implementation(uint32 Num)
{
	MultiOnSkill(Num);
}

void AAIBaseCharacter::MultiOnSkill_Implementation(uint32 Num)
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

void AAIBaseCharacter::TargetRotation()
{
	if (!BaseController) return;
	ACharacter* Target = BaseController->GetTarget();
	if (!Target) return;

	TargetLocation = Target->GetActorLocation();
	RotateToTarget();
}

void AAIBaseCharacter::RotateToTarget()
{
	FVector AILocation = GetActorLocation();

	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(AILocation, TargetLocation);
	FRotator CurrentRotation = GetActorRotation();

	FQuat CurrentQuat = CurrentRotation.Quaternion();
	FQuat TargetQuat = FRotator(CurrentRotation.Pitch, TargetRotation.Yaw, CurrentRotation.Roll).Quaternion();

	FQuat NewQuat = FMath::QInterpTo(CurrentQuat, TargetQuat, GetWorld()->GetDeltaSeconds(), 8.f);

	FRotator NewRotation = NewQuat.Rotator();
	SetActorRotation(NewRotation);
}
