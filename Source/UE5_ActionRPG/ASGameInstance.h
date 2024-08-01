#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interface/MenuInterface.h"
#include "ASGameInstance.generated.h"


UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Warrior UMETA(DisplayName = "Warrior"),
	Assassin UMETA(DisplayName = "Assassin"),
	Katana UMETA(DisplayName = "Katana"),
	Spearman UMETA(DisplayName = "Spearman"),
	_End UMETA(Hidden)
};

USTRUCT()
struct FCharacterData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ECharacterClass CharacterClassName = ECharacterClass::_End;
};


UCLASS()
class UE5_ACTIONRPG_API UASGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UASGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

public:
	UPROPERTY(EditAnywhere)
	FCharacterData CharacterData; 

	UPROPERTY(EditAnywhere)
	TMap<ECharacterClass, TSubclassOf<class ABasePlayer>> CharacterClassMap; 

	UFUNCTION(BlueprintCallable)
	void LoadinGameMenu();


private:
	void OnCreateSessionComplete(FName InSessionName, bool InSuccess);
	void OnDestroySessionComplete(FName InSessionName, bool InSuccess);
	void OnFindSessionsComplete(bool InSuccess);
	void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InResult);

	void OnNetworkFailure(UWorld* InWorld, UNetDriver* InNetDriver, ENetworkFailure::Type InType, const FString& ErrorSting);
	void CreateSession();

	UFUNCTION(BlueprintCallable, Exec)
	void LoadMainMenu();

	UFUNCTION(Exec)
	void Host(FString InServerName) override;


	UFUNCTION(Exec)
	void Join(uint32 Index) override;

	void LoadMainMenuLevel() override;

	void RefreshServerList() override;

	void StartSession();
private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	TSubclassOf<class UUserWidget> MainMenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UUI_ServerMenu* MainMenu;
	class UMenuWidget* InGameMenu; 
	FString DesiredServerName;
};
