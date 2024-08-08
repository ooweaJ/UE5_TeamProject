// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct(); 

	// Bind a function pointer to the buttons
	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnResumeButtonClicked); 
	}

	if (ConfigButton)
	{
		ConfigButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnConfigButtonClicked);
	}

	if (ConnectExitButton)
	{
		ConnectExitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnConnectExitButtonClicked); 
	}

	if (GameExitButton)
	{
		GameExitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnGameExitButtonClicked);
	}

}

void UPauseMenuWidget::OnResumeButtonClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(PlayerController))
	{
		BasePlayerController->SetPauseMenuOpened(false); 
		RemoveFromParent(); 
		// UGameplayStatics::SetGamePaused(this, false);
		BasePlayerController->SetInputMode(FInputModeGameOnly());
		BasePlayerController->SetShowMouseCursor(false);
	}
}

void UPauseMenuWidget::OnConfigButtonClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void UPauseMenuWidget::OnConnectExitButtonClicked()
{
	FName LevelPath = TEXT("/Game/_dev/Level/Menu"); 
	UGameplayStatics::OpenLevel(this, LevelPath); 
}

void UPauseMenuWidget::OnGameExitButtonClicked()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		if (PlayerController->IsLocalController())
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
		}
	}
}
