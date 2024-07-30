// Fill out your copyright notice in the Description page of Project Settings.
#include "MISC/LevelTransitionUtils.h"
#include "ASGameInstance.h"
#include "Kismet/GameplayStatics.h"


void LevelTransitionUtils::OpenLevelWithData(UObject* WorldContextObject, const FString& LevelName, const FCharacterData& Data)
{
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if (UASGameInstance* ASGameInstance = Cast<UASGameInstance>(GameInstance))
		{
			ASGameInstance->CharacterData = Data; 
		}
	}

	UGameplayStatics::OpenLevel(WorldContextObject, FName(*LevelName)); 
}
