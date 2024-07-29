#include "Behavior/Service_Boss.h"
#include "Actor/Controller/AIController/BaseAIController.h"
#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Component/BehaviorComponent.h"

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

	float distance = aiPawn->GetDistanceTo(Target);



	if (Target == nullptr)
	{
		behavior->SetWaitMode();
		return;
	}
	else
	{
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
			behavior->SetMeleeMode();
			return;
		}
		else
		{
			behavior->SetApproachMode();
			return;
		}
		
	}
}
