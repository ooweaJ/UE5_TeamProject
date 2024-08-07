#include "Behavior/Service_Boss.h"
#include "Actor/Controller/AIController/BaseAIController.h"
#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Component/BehaviorComponent.h"
#include "Component/StateComponent.h"

UService_Boss::UService_Boss()
{
	NodeName = "Boss";
}

void UService_Boss::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ABaseAIController* controller = Cast<ABaseAIController>(OwnerComp.GetOwner());
	if (!controller) return;

	UBehaviorComponent* behavior = controller->GetComponentByClass<UBehaviorComponent>();
	if (!behavior) return;

	AAIBaseCharacter* aiPawn = Cast<AAIBaseCharacter>(controller->GetPawn());

	ACharacter* Target = behavior->GetTarget();

	if (Target == nullptr)
	{
		behavior->SetWaitMode();
		return;
	}
	else
	{
		float distance = aiPawn->GetDistanceTo(Target);

		if (controller->IsOnUltimate())
		{
			behavior->SetUltimateMode();
			return;
		}
		else if (controller->IsOnSkill())
		{
			behavior->SetSkillMode();
			return;
		}
		else if (controller->GetAttackRange() > distance)
		{
			float RandomValue = FMath::FRand();
			if (RandomValue > 0.5f)
			{
				behavior->SetStrafeMode();
				return;
			}
			else
			{
				behavior->SetMeleeMode();
				return;
			}
		}
		else
		{
			behavior->SetApproachMode();
			return;
		}
		
	}
}
