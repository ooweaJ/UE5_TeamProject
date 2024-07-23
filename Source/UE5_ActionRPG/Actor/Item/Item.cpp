#include "Actor/Item/Item.h"
#include "GameFramework/Character.h"
#include "Actor/Item/Attachment.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::SetItemData(ACharacter* InOnwerCharacter, const FItemActionData* InData)
{
	if (!InData) return;
	ActionData = InData;
	OwnerCharacter = InOnwerCharacter;
	ItemType = InData->ItemType;

	{
		FTransform DefaultTransform;
		AAttachment* Actor = InOnwerCharacter->GetWorld()->SpawnActorDeferred<AAttachment>(InData->Attachment, DefaultTransform, InOnwerCharacter, InOnwerCharacter, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Actor->SetOwnerCharacter(InOnwerCharacter);
		Actor->FinishSpawning(DefaultTransform, true);
		Attachment = Actor;
		Attachment->AttachToComponent(InOnwerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InData->SocketName);
	}
}