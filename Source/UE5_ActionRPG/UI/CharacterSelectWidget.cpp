// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterSelectWidget.h"

void UCharacterSelectWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized(); 

	CharacterSelectButton->OnClicked.AddDynamic(this, &ThisClass::OnCharacterSelectButtonClicked); 
}

void UCharacterSelectWidget::OnCharacterSelectButtonClicked()
{
	if (CharacterSelectButtonClicked.IsBound())
	{
		CharacterSelectButtonClicked.Execute(this); 
	}
}

bool UCharacterSelectWidget::SetCharacterClassName(ECharacterClass InCharacterClass)
{
	//if (!type) { check(false); return false; }

	CharacterClassName = InCharacterClass; 

	FText CharacterClassNameText; 

	switch (InCharacterClass)
	{
	case ECharacterClass::Warrior:
		CharacterClassNameText = FText::FromString(TEXT("Warrior"));
		break; 

	case ECharacterClass::Assassin:
		CharacterClassNameText = FText::FromString(TEXT("Assassin"));
		break;

	case ECharacterClass::Swordman:
		CharacterClassNameText = FText::FromString(TEXT("Swordman"));
		break; 

	case ECharacterClass::Spearman:
		CharacterClassNameText = FText::FromString(TEXT("Spearman"));
		break; 

	}

	CharacterClassTextBlock->SetText(CharacterClassNameText); 

	return true; 
}

ECharacterClass UCharacterSelectWidget::GetCharacterClassName() const
{
	return CharacterClassName;
}
