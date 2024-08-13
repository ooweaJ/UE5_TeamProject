#include "Actor/Character/AI/Grux.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actor/ProJectile/GruxMeteor.h"
#include "Actor/Controller/AIController/BaseAIController.h"
#include "Net/UnrealNetwork.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Component/StatusComponent.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/InGameHUD.h"
#include "UI/InGame/UI_MainInGame.h"
#include "UI/InGame/UI_BossStatus.h"

void AGrux::BeginPlay()
{
    Super::BeginPlay();

    TimerDel.BindUFunction(this, FName("SpawnActorsAround"), 500.f, int32(6));
    
    if(UIPopCollision)
        UIPopCollision->OnComponentBeginOverlap.AddDynamic(this, &AGrux::OnUIPopUP);
}

void AGrux::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        if (bFly)
        {
            FVector location = UKismetMathLibrary::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, 2.f);
            SetActorLocation(location);
        }
    }
}

void AGrux::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AGrux, bFly);
}

void AGrux::OnFlySkill(FActionData* InData)
{
    Data = InData;
    FVector CurrentLocation = GetActorLocation();

    // 캐릭터의 뒷대각 위 방향 벡터를 계산합니다.
    // 뒤쪽 방향 벡터 (ForwardVector의 반대)
    FVector BackwardVector = -GetActorForwardVector();
    // 위쪽 방향 벡터 (UpVector)
    FVector UpVector = GetActorUpVector();

    // 뒷대각 위 방향 벡터를 계산합니다.
    FVector DiagonalUpwardDirection = (BackwardVector + UpVector).GetSafeNormal();

    // 이동할 위치를 계산합니다.
    TargetLocation = CurrentLocation + DiagonalUpwardDirection * 1500.f;

    bFly = true;

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 3.0f, false);
}

void AGrux::SpawnActorsAround(float Distance, int32 NumberOfActors)
{
    FVector Origin = GetActorLocation();
    FRotator Rotation = GetActorRotation();

    for (int32 i = 1; i <= NumberOfActors; ++i)
    {
        float Angle = i * (360.0f / NumberOfActors);
        float Radian = FMath::DegreesToRadians(Angle);

        // Z축을 기준으로 원형 배치
        FVector SpawnLocation = Origin + FVector(0,  FMath::Sin(Radian) * Distance, FMath::Cos(Radian) * Distance);

        // 액터의 회전은 Z축을 기준으로 조정합니다.
        FRotator SpawnRotation = FRotator(0, Angle, 0);

        if (ActorToSpawn)
        {
            if (!BaseController) return;
            AGruxMeteor* Meteor = GetWorld()->SpawnActor<AGruxMeteor>(ActorToSpawn, SpawnLocation, SpawnRotation);
            Meteor->SetTarget(BaseController->GetTarget());
            Meteor->SetOwner(this);
            Meteor->SetData(Data);
            Meteor->OnTarget(i);
        }
    }
    UKismetSystemLibrary::K2_SetTimer(this, "FinishFlySkill", 4.f, false);
}

void AGrux::OnUIPopUP(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ABasePlayer* BP = Cast<ABasePlayer>(OtherActor);
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (AInGameHUD* InGameHUD = Cast<AInGameHUD>(PC->GetHUD()))
        {
            if (UUI_MainInGame* UI = Cast<UUI_MainInGame>(InGameHUD->MainUI))
            {
                UI->UI_BossStatus = Cast<UUI_BossStatus>(HealthWidget->GetUserWidgetObject());
                UI->UI_BossStatus->SetHP(Status->GetHealth(), Status->GetMaxHealth());
                UI->UI_BossStatus->SetVisibility(ESlateVisibility::Visible);
            }
        }
    }
}


void AGrux::FinishFlySkill_Implementation()
{
    MultiFinishFlySkill();
}

void AGrux::MultiFinishFlySkill_Implementation()
{
    if (FlyAttack)
    {
        bFly = false;
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
        PlayAnimMontage(FlyAttack);
    }
}
