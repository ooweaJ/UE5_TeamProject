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

UENUM() 
enum class EMenu : uint8
{
	Main,
	CharacterSelect
};

UCLASS()
class UE5_ACTIONRPG_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override; 

	void SetButtonNormalStyle(UButton* InButton, FLinearColor InLinearColor = FLinearColor(1.f, 1.f, 1.f, 0.f)); 
	void Setup();
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

private:
	UButton* CurrentClickedButton = nullptr; 
	UButton* LastClickedButton = nullptr; 
};
