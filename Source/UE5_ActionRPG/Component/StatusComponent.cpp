#include "Component/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Mana = MaxMana;
	Stamina = MaxStamina;
}

void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStatusComponent::SetSpeed(EWalkSpeedTpye InType)
{
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	if(movement)
		movement->MaxWalkSpeed = Speed[(int32)InType];
}

void UStatusComponent::IncreaseHealth(float InAmount)
{
	Health += InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

void UStatusComponent::DecreaseHealth(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.f, MaxHealth);
}

void UStatusComponent::SetDamage(float InAmount)
{
	Damage = InAmount;
}

void UStatusComponent::IncreaseMans(float InAmount)
{
	Mana += InAmount;
	Mana = FMath::Clamp(Mana, 0.f, MaxMana);
}

void UStatusComponent::DecreaseMana(float InAmount)
{
	Mana -= InAmount;
	Mana = FMath::Clamp(Mana, 0.f, MaxMana);
}

void UStatusComponent::IncreaseStamina(float InAmount)
{
	Stamina += InAmount;
	Stamina = FMath::Clamp(Stamina, 0.f, MaxStamina);
}

void UStatusComponent::DecreaseStamina(float InAmount)
{
	Stamina -= InAmount;
	Stamina = FMath::Clamp(Stamina, 0.f, MaxStamina);
}

void UStatusComponent::SetStaminaRegen(float InAmount)
{
	StaminaRegen = InAmount;
}

float UStatusComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

float UStatusComponent::GetManaPercent()
{
	return Mana / MaxMana;
}

float UStatusComponent::GetStaminaPercent()
{
	return Stamina / MaxStamina;
}