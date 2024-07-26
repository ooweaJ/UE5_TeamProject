#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "ASGameInstance.generated.h"

UCLASS()
class UE5_ACTIONRPG_API UASGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UASGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

private:
	void OnCreateSessionComplete(FName InSessionName, bool InSuccess);
	void OnDestroySessionComplete(FName InSessionName, bool InSuccess);
	void OnFindSessionsComplete(bool InSuccess);
	void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InResult);

	void OnNetworkFailure(UWorld* InWorld, UNetDriver* InNetDriver, ENetworkFailure::Type InType, const FString& ErrorSting);
	void CreateSession();

	void Host();
private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
};
