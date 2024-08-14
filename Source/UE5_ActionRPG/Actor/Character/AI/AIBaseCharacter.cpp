#include "Actor/Character/AI/AIBaseCharacter.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"
#include "Component/EquipComponent.h"
#include "Actor/Item/Item.h"
#include "Actor/Controller/AIController/BaseAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/InGame/UI_BossStatus.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/InGameHUD.h"
#include "UI/InGame/UI_MainInGame.h"
#include "Actor/Character/Player/BasePlayer.h"

AAIBaseCharacter::AAIBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthWidget->SetupAttachment(RootComponent);
	
	UIPopCollision = CreateDefaultSubobject<USphereComponent>(TEXT("UIPopCollision"));
	UIPopCollision->SetupAttachment(RootComponent);
	UIPopCollision->SetSphereRadius(1500.f);

	ConstructorHelpers::FClassFinder<UUserWidget> Class(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/InGame/BPUI_BossStatus.BPUI_BossStatus_C'"));
	if(Class.Succeeded())
		HealthWidget->SetWidgetClass(Class.Class);

	UIPopCollision->OnComponentBeginOverlap.AddDynamic(this, &AAIBaseCharacter::OnUIPopUP);
	UIPopCollision->OnComponentEndOverlap.AddDynamic(this, &AAIBaseCharacter::OnUIOff);
}

void AAIBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UUI_BossStatus* AIStatus = Cast<UUI_BossStatus>(HealthWidget->GetUserWidgetObject()))
	{
		AIStatus->SetHP(Status->GetHealth(), Status->GetMaxHealth());
		AIStatus->SetNameTag(NameTag);
	}
	if (ABaseAIController* controller = Cast<ABaseAIController>(GetController()))
	{
		BaseController = controller;
	}
}

void AAIBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStrafe)
	{
		if (Status->IsCanMove())
		{
			if (Direction != FVector::ZeroVector)
			{
				AddMovementInput(Direction);
			}
		}
	}

	if (bRotate)
	{
		TargetRotation();
	}

	
	if(APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		FVector PlayerLocation = PlayerPawn->GetActorLocation();

		FVector WidgetLocation = HealthWidget->K2_GetComponentLocation();

		FRotator RotateVal = UKismetMathLibrary::FindLookAtRotation(WidgetLocation, PlayerLocation);
		HealthWidget->SetWorldRotation(RotateVal);
	}
}

void AAIBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAIBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float TempDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	return TempDamage;
}

void AAIBaseCharacter::OnMelee_Implementation(uint32 Num)
{
	MultiOnMelee(Num);
}

void AAIBaseCharacter::MultiOnMelee_Implementation(uint32 Num)
{
	if (!State && !Equip) return;

	if (AItem* Item = Equip->GetCurrentItem())
	{
		switch (Num)
		{
		case 1:
		{
			Item->OnDefaultAction();
			break;
		}
		case 2:
		{
			Item->OnDefaultAction2();
			break;
		}
		case 3:
		{
			Item->OnDefaultAction3();
			break;
		}
		}
	}
}

void AAIBaseCharacter::OnSkill_Implementation(uint32 Num)
{
	MultiOnSkill(Num);
}

void AAIBaseCharacter::MultiOnSkill_Implementation(uint32 Num)
{
	if (!State && !Equip) return;
	State->SetActionMode();
	if (AItem* Item = Equip->GetCurrentItem())
	{
		switch (Num)
		{
		case 1:
		{
			Item->OnSkillAction();
			break;
		}
		case 2:
		{
			Item->OnSkillAction2();
			break;
		}
		case 3:
		{
			Item->OnSkillAction3();
			break;
		}
		}
	}
}

void AAIBaseCharacter::OnUltimate()
{
	if (!State && !Equip) return;
	State->SetActionMode();
	if (AItem* Item = Equip->GetCurrentItem())
		Item->OnUltimateAction();
}

void AAIBaseCharacter::OffMelee()
{
}

void AAIBaseCharacter::OffSkill()
{
}

void AAIBaseCharacter::OffUltimate()
{
}

void AAIBaseCharacter::TargetRotation()
{
	if (!BaseController) return;
	ACharacter* Target = BaseController->GetTarget();
	if (!Target) return;

	TargetLocation = Target->GetActorLocation();
	RotateToTarget();
}

void AAIBaseCharacter::RotateToTarget()
{
	FVector AILocation = GetActorLocation();

	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(AILocation, TargetLocation);
	FRotator CurrentRotation = GetActorRotation();

	FQuat CurrentQuat = CurrentRotation.Quaternion();
	FQuat TargetQuat = FRotator(CurrentRotation.Pitch, TargetRotation.Yaw, CurrentRotation.Roll).Quaternion();

	FQuat NewQuat = FMath::QInterpTo(CurrentQuat, TargetQuat, GetWorld()->GetDeltaSeconds(), 8.f);

	FRotator NewRotation = NewQuat.Rotator();
	SetActorRotation(NewRotation);
}

void AAIBaseCharacter::UpdateHP()
{
	Super::UpdateHP();
	if (UUI_BossStatus* AIStatus = Cast<UUI_BossStatus>(HealthWidget->GetUserWidgetObject()))
	{
		AIStatus->SetHP(Status->GetHealth(), Status->GetMaxHealth());
	}

	if (ActorHasTag("Boss"))
	{
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			if (AInGameHUD* HUD = Cast<AInGameHUD>(PC->GetHUD()))
				if (UUI_MainInGame* InGameUI = Cast<UUI_MainInGame>(HUD->MainUI))
				{
					InGameUI->BPUI_BossStatus->SetHP(Status->GetHealth(), Status->GetMaxHealth());
					InGameUI->BPUI_BossStatus->SetNameTag(NameTag);
				}
	}
}

void AAIBaseCharacter::OnUIPopUP(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABasePlayer* BP = Cast<ABasePlayer>(OtherActor);
	if (!BP) return;

	if (ActorHasTag("Boss"))
	{
		if (APlayerController* PC = Cast<APlayerController>(BP->GetController()))
			if (AInGameHUD* HUD = Cast<AInGameHUD>(PC->GetHUD()))
				if (UUI_MainInGame* InGameUI = Cast<UUI_MainInGame>(HUD->MainUI))
				{
					InGameUI->BPUI_BossStatus->SetVisibility(ESlateVisibility::Visible);
					HealthWidget->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Collapsed);
				}
	}
}

void AAIBaseCharacter::OnUIOff(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABasePlayer* BP = Cast<ABasePlayer>(OtherActor);
	if (!BP) return;

	if (ActorHasTag("Boss"))
	{
		if (APlayerController* PC = Cast<APlayerController>(BP->GetController()))
			if (AInGameHUD* HUD = Cast<AInGameHUD>(PC->GetHUD()))
				if (UUI_MainInGame* InGameUI = Cast<UUI_MainInGame>(HUD->MainUI))
				{
					InGameUI->BPUI_BossStatus->SetVisibility(ESlateVisibility::Collapsed);
					HealthWidget->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
				}
	}
}

void AAIBaseCharacter::PlayRateMontage_Implementation()
{
	MultiPlayRateMontage();
}

void AAIBaseCharacter::MultiPlayRateMontage_Implementation()
{
	if (Equip)
		Equip->GetCurrentItem()->MontagePlayRate(GetMesh()->GetAnimInstance(), 0.3f);
}
