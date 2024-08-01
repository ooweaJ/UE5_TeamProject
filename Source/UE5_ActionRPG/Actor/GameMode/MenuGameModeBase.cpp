// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/GameMode/MenuGameModeBase.h"
#include "Actor/Controller/PlayerController/MenuPlayerController.h"

AMenuGameModeBase::AMenuGameModeBase()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass(); 
}

void AMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay(); 

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController(); 
	if (AMenuPlayerController* MenuPlayerController = Cast<AMenuPlayerController>(PlayerController))
	{
		MenuPlayerController->SetShowMouseCursor(true); 
	}
}

void AMenuGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason); 
}