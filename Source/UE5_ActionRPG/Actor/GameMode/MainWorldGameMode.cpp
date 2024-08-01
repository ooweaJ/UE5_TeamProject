#include "Actor/GameMode/MainWorldGameMode.h"
#include "Actor/Character/Player/BasePlayer.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"
#include "Actor/PlayerState/BasePlayerState.h"
#include "ASGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"


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
	++NumberOfPlayers;

	if (UASGameInstance* ASGameInstance = Cast<UASGameInstance>(GetWorld()->GetGameInstance()))
	{
		if (ASGameInstance->CharacterData.CharacterClassName != ECharacterClass::_End)
		{
			TSubclassOf<ABasePlayer>* BasePlayer = ASGameInstance->CharacterClassMap.Find(ASGameInstance->CharacterData.CharacterClassName); 
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
}

void AMainWorldGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMainWorldGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
