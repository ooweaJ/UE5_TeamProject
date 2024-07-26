#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class UE5_ACTIONRPG_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	uint32 NumberOfPlayers = 0;
};
