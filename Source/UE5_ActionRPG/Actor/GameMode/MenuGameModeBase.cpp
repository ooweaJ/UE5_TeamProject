// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/GameMode/MenuGameModeBase.h"
#include "UI/MenuWidget.h"
#include "Kismet/GameplayStatics.h"

AMenuGameModeBase::AMenuGameModeBase()
{
	static ConstructorHelpers::FClassFinder<UMenuWidget> FindClass
	{
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/Menu/UI_Menu.UI_Menu_C'")
	};

	ensure(FindClass.Class); 
	MenuWidgetClass = FindClass.Class; 
}

void AMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay(); 

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true); 
	}

	MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass); 
	MenuWidget->AddToViewport(); 
}

void AMenuGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason); 
}
