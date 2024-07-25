#include "Actor/Character/Player/BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Component/StatusComponent.h"
#include "Component/StateComponent.h"
#include "Actor/PlayerState/BasePlayerState.h"
#include "AbilitySystem/Attributes/PlayerAttributeSet.h"

ABasePlayer::ABasePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;


	{
		StatusComponent = CreateDefaultSubobject<UStatusComponent>("StatusComponent");
		StateComponent = CreateDefaultSubobject<UStateComponent>("StateComponent");
	}

	{
		USkeletalMeshComponent* mesh = GetMesh();
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
		if (!Asset.Succeeded()) return;

		mesh->SetSkeletalMesh(Asset.Object);
		mesh->SetRelativeLocation(FVector(0, 0, -88));
		mesh->SetRelativeRotation(FRotator(0, -90, 0));
	}

	{
		SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
		SpringArm->SetupAttachment(RootComponent);

		Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
		Camera->SetupAttachment(SpringArm);

		SpringArm->SetRelativeLocation(FVector(0, 0, 90));
		SpringArm->TargetArmLength = 300.f;
		SpringArm->bDoCollisionTest = true;
		SpringArm->bUsePawnControlRotation = true;
	}
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// Temp
	if (Test && AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Test, 1, EffectContext);

		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void ABasePlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystem();
}

void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePlayer::InitAbilitySystem()
{
	if (ABasePlayerState* PS = GetPlayerState<ABasePlayerState>())
	{
		AbilitySystemComponent = Cast<UBaseAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		AttributeSet = PS->GetPlayerSet();
	}
}

UAbilitySystemComponent* ABasePlayer::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}