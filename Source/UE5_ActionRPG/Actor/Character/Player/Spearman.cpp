// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/Player/Spearman.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/SkinnedAssetCommon.h"
#include "Animation/AnimBlueprint.h"
#include "Actor/Item/Weapon/SpearWeapon.h"

ASpearman::ASpearman(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent2D")); 
	SceneCaptureComponent2D->SetupAttachment(GetRootComponent()); 

	{
		static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RenderTarget(TEXT("/Script/Engine.TextureRenderTarget2D'/Game/_dev/Actor/Character/Player/Spear/RT_Spear.RT_Spear'"));
		ensure(RenderTarget.Object);
		SceneCaptureComponent2D->TextureTarget = RenderTarget.Object; 
	}

	{
		static ConstructorHelpers::FClassFinder<UAnimInstance> ABPClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Retargeted_Asset/ABP_Spearman.ABP_Spearman_C'"));
		ensure(ABPClass.Class); 
		GetMesh()->SetAnimInstanceClass(ABPClass.Class); 
	}
	

}

void ASpearman::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform); 

	if (USkeletalMeshComponent* CharacterMesh = Cast<USkeletalMeshComponent>(GetMesh()))
	{
		const TArray<FSkeletalMaterial>& SkeletalMaterials = CharacterMesh->GetSkinnedAsset()->GetMaterials(); 
		const int32 MaterialNum = SkeletalMaterials.Num(); 
		for (int32 i = 0; i < MaterialNum; ++i)
		{
			UMaterialInstanceDynamic* MID = CharacterMesh->CreateDynamicMaterialInstance(i, SkeletalMaterials[i].MaterialInterface); 
			MID->SetVectorParameterValue(TEXT("Color"), FVector4(0.f, 1.f, 0.f, 1.f));
		}
	}

	DefaultItemClass = ASpearWeapon::StaticClass(); 
}

float ASpearman::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}
