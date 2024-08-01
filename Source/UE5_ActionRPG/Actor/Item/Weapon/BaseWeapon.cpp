// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/BaseWeapon.h"
#include "Actor/Item/Attachment.h"
#include "Actor/Character/BaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Component/StatusComponent.h"

ABaseWeapon::ABaseWeapon()
{
}

void ABaseWeapon::BeginPlay()
{
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &ThisClass::OnDamage);
}

void ABaseWeapon::OnDamage(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(InAttacker);
	AController* LocalInstigator = BaseCharacter->GetController();
	float LocalDamage = BaseCharacter->GetStatusComponent()->GetDamage() + WeaponDamage;
	UGameplayStatics::ApplyDamage(InOtherCharacter, LocalDamage, LocalInstigator, InCauser, UDefaultDamageType::StaticClass());
}