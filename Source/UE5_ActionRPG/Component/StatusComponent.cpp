#include "Component/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	StatusRegen(HP);
	StatusRegen(MP);
	StatusRegen(SP);
}

void UStatusComponent::SetSpeed(EWalkSpeedTpye InType)
{
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	if(movement)
		movement->MaxWalkSpeed = Speed[(int32)InType];
}

void UStatusComponent::StatusModify(UPARAM(ref) FStatus& Status, float InAmount)
{
	Status.Current = FMath::Clamp(Status.Current+InAmount, 0.f, Status.Max);
}

float UStatusComponent::StatusPersent(const FStatus& Status)
{
	return Status.Current / Status.Max;
}

void UStatusComponent::StatusRegen(FStatus& Status)
{
	if (Status.bRegen)
	{
		Status.Current = FMath::Clamp(Status.Current + (Status.Regen*GetWorld()->GetDeltaSeconds()), 0.f, Status.Max);
	}
}

void UStatusComponent::SetDamage(float InAmount)
{
	Damage = InAmount;
}


