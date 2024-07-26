#include "ASGameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemTypes.h"
#include "Engine.h"

const static FName SESSION_NAME = TEXT("GameSession");
const static FName SEVER_NAME_SETTINGS_KEY = TEXT("ServerName");

UASGameInstance::UASGameInstance(const FObjectInitializer& ObjectInitializer)
{
}

void UASGameInstance::Init()
{
	IOnlineSubsystem* oss = IOnlineSubsystem::Get();   
	if (!!oss)
	{
		SessionInterface = oss->GetSessionInterface();

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("SubSystem : %s"), *oss->GetSubsystemName().ToString()));
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ThisClass::OnCreateSessionComplete);  
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &ThisClass::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &ThisClass::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &ThisClass::OnJoinSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Not found OSS"));
	}

	if (!!GEngine)
		GEngine->OnNetworkFailure().AddUObject(this, &ThisClass::OnNetworkFailure);
}

void UASGameInstance::OnCreateSessionComplete(FName InSessionName, bool InSuccess)
{
	if (InSuccess == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not Create Session"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Session : %s"), *InSessionName.ToString());


	UWorld* world = GetWorld();
	if (world == nullptr) return;
	world->ServerTravel("/Game/Maps/MainWorld?listen");
}

void UASGameInstance::OnDestroySessionComplete(FName InSessionName, bool InSuccess)
{
	if (InSuccess == true)
		CreateSession();
}

void UASGameInstance::OnFindSessionsComplete(bool InSuccess)
{
}

void UASGameInstance::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InResult)
{
}

void UASGameInstance::OnNetworkFailure(UWorld* InWorld, UNetDriver* InNetDriver, ENetworkFailure::Type InType, const FString& ErrorSting)
{
}

void UASGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings sessionSettiongs;
		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			sessionSettiongs.bIsLANMatch = true;
		}
		else
		{
			sessionSettiongs.bIsLANMatch = false;
		}
		sessionSettiongs.NumPublicConnections = 4;
		sessionSettiongs.bShouldAdvertise = true;
		sessionSettiongs.bUsesPresence = true;
		sessionSettiongs.Set(SEVER_NAME_SETTINGS_KEY, FString("AS"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, sessionSettiongs);
	}
}

void UASGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto exsistiongSession = SessionInterface->GetNamedSession(SESSION_NAME);

		if (!!exsistiongSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}
