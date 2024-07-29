// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MenuWidget.generated.h"

class UCharacterSelectWidget; 

namespace EMenu
{
	enum type
	{
		Main, 
		CharacterSelect
	};
}


UCLASS()
class UE5_ACTIONRPG_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override; 

public:
	UFUNCTION()
	void OnConnectButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

	UFUNCTION()
	void OnOptionButtonClicked();

	UFUNCTION()
	void OnSelectStartButtonClicked();

	UFUNCTION()
	void OnSelectGoBackButtonClicked();

	UFUNCTION()
	void OnCharacterClassButtonClicked(UCharacterSelectWidget* InWidget); 

	
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ConnectButton; 

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* SelectStartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* SelectGoBackButton;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher; 

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUniformGridPanel* CharacterGridPanel; 

	UPROPERTY()
	TSubclassOf<UCharacterSelectWidget> CharacterSelectWidgetClass; 

protected:
	virtual void PopulateGrid(); 
};
