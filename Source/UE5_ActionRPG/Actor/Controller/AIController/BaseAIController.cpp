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

ABaseAIController::ABaseAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");
	Behavior = CreateDefaultSubobject<UBehaviorComponent>("Behavior");
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = SightRadius;
	Sight->LoseSightRadius = SightRadius;
	Sight->PeripheralVisionAngleDegrees = 360.0f;
	Sight->SetMaxAge(2.f);

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(Sight->GetSenseImplementation());

	//static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/_dev/BB_AIDefault.BB_AIDefault'"));
	//if (BBObject.Succeeded())
	//{
	//	BBAsset = BBObject.Object;
	//}
	//static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/_dev/BT_AIDefault.BT_AIDefault'"));
	//if (BTObject.Succeeded())
	//{
	//	BTAsset = BTObject.Object;
	//}
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
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
	Perception->OnPerceptionUpdated.AddDynamic(this, &ThisClass::OnPerceptionUpdated);
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

void ABaseAIController::SetLoactionKey(FVector InLoaction)
{
	Blackboard->SetValueAsVector(FBlackBoardKeyNameTable::LocationKey, InLoaction);
}

void ABaseAIController::SetTargetKey(ACharacter* InCharacter)
{
	Blackboard->SetValueAsObject(FBlackBoardKeyNameTable::TargetKey, InCharacter);
}