// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/GameMode/LoadingGameModeBase.h"
#include "Actor/Controller/PlayerController/LoadingPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ASGameInstance.h"

ALoadingGameModeBase::ALoadingGameModeBase()
{
	bUseSeamlessTravel = true; 

	PlayerControllerClass = ALoadingPlayerController::StaticClass(); 
}

void ALoadingGameModeBase::BeginPlay()
{
	Super::BeginPlay(); 

	if (UASGameInstance* ASGameInstance = Cast<UASGameInstance>(GetGameInstance()))
	{
		const FString& PlayerClass = ASGameInstance->GetClassName();
		ReceivedOptions = PlayerClass;
		TMap<ENetworkRole, FTravelInfo> TravelInfos = ASGameInstance->GetTravelInfos();

		if (TravelInfos.Contains(ENetworkRole::Server))
		{
			AsyncLoadMap(TEXT("/Game/_dev/Level/MainWorld?Listen"));
		}
		else
		{
			FString ClientTravelURL = TravelInfos[ENetworkRole::Client].TravelURL; 
			AsyncLoadMap(ClientTravelURL); 
		}
	}

}

void ALoadingGameModeBase::OnMapLoadComplete(const FString& DestinationPath)
{
	LoadComplete(DestinationPath, 2.f); 
}

void ALoadingGameModeBase::AsyncLoadMap(const FString& DestinationPath)
{
	UGameplayStatics::LoadStreamLevel(this, FName(*DestinationPath), true, false, FLatentActionInfo()); 

	FTimerDelegate TimerDelegate; 
	TimerDelegate.BindUFunction(this, FName("OnMapLoadComplete"), DestinationPath); 
	GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate); 
}

void ALoadingGameModeBase::LoadComplete(const FString& DestinationPath, float DelayTime)
{
	FTimerDelegate LoadCompleteTimerDelegate;
	LoadCompleteTimerDelegate.BindLambda([this, DestinationPath]()
		{
			GetWorld()->ServerTravel(DestinationPath + TEXT("?") + ReceivedOptions, false);
		}
	);
	GetWorld()->GetTimerManager().SetTimer(DelayTravelTimerHandle, LoadCompleteTimerDelegate, DelayTime, false);
}