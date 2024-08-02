#include "Actor/GameMode/MainWorldGameMode.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"
#include "Actor/PlayerState/BasePlayerState.h"
#include "ASGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Engine.h"

AMainWorldGameMode::AMainWorldGameMode()
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
	{
		ConstructorHelpers::FClassFinder<ABasePlayer> Class = TEXT("/Script/Engine.Blueprint'/Game/_dev/Actor/Character/Player/BP_BasePlayer.BP_BasePlayer_C'");
		ensure(Class.Class);
		DefaultPawnClass = Class.Class;
		PlayerStateClass = ABasePlayerState::StaticClass();
	}
}

void AMainWorldGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	{
		TSubclassOf<ABasePlayer>* BasePlayer = ClassMap.Find(ClassName);
		if (!BasePlayer) { check(false); return; }

		APlayerStart* PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass())); 
		if (!PlayerStart) { check(false); return; }

		FVector SpawnLocation = PlayerStart->GetActorLocation(); 
		FRotator SpawnRotation = PlayerStart->GetActorRotation(); 
		FActorSpawnParameters SpawnParams; 
		SpawnParams.Owner = NewPlayer; 

		ABasePlayer* NewBasePlayer = GetWorld()->SpawnActor<ABasePlayer>(*BasePlayer, SpawnLocation, SpawnRotation, SpawnParams); 
		if (!NewBasePlayer) { check(false); return; }
		
		if (AActor* Pawn = NewPlayer->GetPawn())
			Pawn->Destroy();

		NewPlayer->Possess(NewBasePlayer); 
	}
}

APlayerController* AMainWorldGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* PC = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	const FString Class = UGameplayStatics::ParseOption(Options, "Class");
	ClassName = Class;
	return PC;
}

void AMainWorldGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMainWorldGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
