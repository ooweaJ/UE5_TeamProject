// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/SpearWeapon.h"
#include "Data/ActionData/CombatActionDataAsset.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Kismet/KismetMathLibrary.h"


ASpearWeapon::ASpearWeapon()
{
	{
		static ConstructorHelpers::FObjectFinder<UCombatActionDataAsset> DA(TEXT("/Script/UE5_ActionRPG.CombatActionDataAsset'/Game/_dev/Data/DA/DA_Spearman.DA_Spearman'"));
		ensure(DA.Object); 
		ItemData = DA.Object; 
	}	
}

void ASpearWeapon::OnSkillAction()
{
	if (true/*bCanCombo*/)
	{
		// world에서 spawn되고 관련 값을 spear projectile에 전달하는 함수를 만들어야 
		
	}

}

void ASpearWeapon::OnSkillAction2()
{
	
}

