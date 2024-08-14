// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoadingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5_ACTIONRPG_API ALoadingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALoadingGameModeBase(); 

protected:
	virtual void BeginPlay() override; 

protected:
	UFUNCTION()
	void OnMapLoadComplete(const FString& DestinationPath); 

	void AsyncLoadMap(const FString& DestinationPath);

	void LoadComplete(const FString& DestinationPath, float DelayTime); 

protected:
	FTimerHandle DelayTravelTimerHandle;

private:
	FString ReceivedOptions; 
};
