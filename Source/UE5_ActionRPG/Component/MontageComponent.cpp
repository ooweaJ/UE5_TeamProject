#include "Component/MontageComponent.h"

UMontageComponent::UMontageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMontageComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UMontageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

