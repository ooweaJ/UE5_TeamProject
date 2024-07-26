#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainWorldGameMode.generated.h"

UCLASS()
class UE5_ACTIONRPG_API AMainWorldGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMainWorldGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	uint32 NumberOfPlayers = 0;
};
