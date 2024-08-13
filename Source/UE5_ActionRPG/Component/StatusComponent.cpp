#include "Component/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/CombatInterface.h"
#include "Net/UnrealNetwork.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	if (GetOwner()->HasAuthority())
	{
		OnRep_Update();
	}
}

void UStatusComponent::SetDamage(float InAmount)
{
	Damage = InAmount;
}


void UStatusComponent::IncreaseHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
	if (GetOwner()->HasAuthority())
	{
		OnRep_Update();
	}
}

void UStatusComponent::DecreaseHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
	if (GetOwner()->HasAuthority())
	{
		OnRep_Update();
	}
}

void UStatusComponent::OnRep_Update()
{
	if (ICombatInterface* Combat = Cast<ICombatInterface>(GetOwner()))
	{
		Combat->UpdateHP();
	}
}

void UStatusComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStatusComponent, Health);
	DOREPLIFETIME(UStatusComponent, HP);
}