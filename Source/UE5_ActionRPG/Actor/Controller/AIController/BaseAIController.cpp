#include "Actor/Controller/AIController/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "GameFrameWork/Character.h"

#include "Component/BehaviorComponent.h"
#include "Actor/Character/AI/AIBaseCharacter.h"
#include "MISC/MISC.h"
#include "Kismet/KismetSystemLibrary.h"

ABaseAIController::ABaseAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");
	Behavior = CreateDefaultSubobject<UBehaviorComponent>("Behavior");
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = SightRadius;
	Sight->LoseSightRadius = SightRadius + 500;
	Sight->PeripheralVisionAngleDegrees = 360.0f;
	Sight->SetMaxAge(2.f);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(Sight->GetSenseImplementation());
	Perception->OnPerceptionUpdated.AddDynamic(this, &ThisClass::OnPerceptionUpdated);

}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	UKismetSystemLibrary::K2_SetTimer(this, "CooldownSkill", 15.f, false);
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerAI = Cast<AAIBaseCharacter>(InPawn);
	if (!OwnerAI) return;
	UBlackboardComponent* BlackboardPtr = Blackboard;
	UseBlackboard(BBAsset, BlackboardPtr);
	Behavior->SetBlackBoard(Blackboard);
	RunBehaviorTree(BTAsset);
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}

void ABaseAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	ACharacter* player = nullptr;
	for (AActor* actor : actors)
	{
		player = Cast<ACharacter>(actor);

		if (!!player)
			break;
	}

	Blackboard->SetValueAsObject(FBlackBoardKeyNameTable::TargetKey, player);
}

void ABaseAIController::CooldownSkill()
{
	bSkill = true;
}

void ABaseAIController::SetLoactionKey(FVector InLoaction)
{
	Blackboard->SetValueAsVector(FBlackBoardKeyNameTable::LocationKey, InLoaction);
}

void ABaseAIController::SetTargetKey(ACharacter* InCharacter)
{
	Blackboard->SetValueAsObject(FBlackBoardKeyNameTable::TargetKey, InCharacter);
}

void ABaseAIController::OnMeleeAttack()
{
	uint32 num = FMath::RandRange(1, 2);
	OwnerAI->OnMelee(num);
}

void ABaseAIController::OnSkill(uint32 Num)
{
	OwnerAI->OnSkill(Num);
	bSkill = false;
	UKismetSystemLibrary::K2_SetTimer(this, "CooldownSkill", 15.f, false);
}

void ABaseAIController::OnUltimate()
{
	OwnerAI->OnUltimate();
}

ACharacter* ABaseAIController::GetTarget()
{
	return Behavior->GetTarget();
}
