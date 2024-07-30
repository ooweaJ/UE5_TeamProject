// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuWidget.h"
#include "UI/CharacterSelectWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Load and Find CharacterSelectWidget
	LoadClass<UClass>(ANY_PACKAGE, 
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/Menu/UI_CharacterSelect.UI_CharacterSelect_C'"), nullptr, LOAD_None, nullptr);

	CharacterSelectWidgetClass = FindObject<UClass>(
		ANY_PACKAGE,
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/_dev/UI/Menu/UI_CharacterSelect.UI_CharacterSelect_C'"));

	// Place character class on grid in CharacterSelectWidget
	PopulateGrid(); 


	// Bind a function pointer to the buttons
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnExitButtonClicked); 
	}

	if (ConnectButton)
	{
		ConnectButton->OnClicked.AddDynamic(this, &UMenuWidget::OnConnectButtonClicked); 
	}

	if (SelectGoBackButton)
	{
		SelectGoBackButton->OnClicked.AddDynamic(this, &UMenuWidget::OnSelectGoBackButtonClicked); 
	}

}


void UMenuWidget::OnConnectButtonClicked()
{
	MenuSwitcher->SetActiveWidgetIndex(static_cast<int32>(EMenu::CharacterSelect));
}

void UMenuWidget::OnExitButtonClicked()
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

void UMenuWidget::OnOptionButtonClicked()
{
}

void UMenuWidget::OnSelectStartButtonClicked()
{
}

void UMenuWidget::OnSelectGoBackButtonClicked()
{
	// 클릭했던 정보들을 cache할 것인지??
	MenuSwitcher->SetActiveWidgetIndex(static_cast<int32>(EMenu::Main)); 
}

void UMenuWidget::OnCharacterClassButtonClicked(UCharacterSelectWidget* InWidget)
{
}

void UMenuWidget::PopulateGrid()
{
	if (!CharacterGridPanel || !CharacterSelectWidgetClass) { return; }

	int32 Row = 0; 
	int32 Column = 0; 

	for (int i = 0; i < ECharacterClass::_End; ++i)
	{
		UCharacterSelectWidget* CharacterSelectWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), CharacterSelectWidgetClass);

		bool bSetCharClassName = CharacterSelectWidget->SetCharacterClassName(static_cast<ECharacterClass::type>(i));

		if (!bSetCharClassName){check(false); return; }

		UUniformGridSlot* GridSlot = CharacterGridPanel->AddChildToUniformGrid(CharacterSelectWidget, Row, Column); 

		++Column; 
	}

}
