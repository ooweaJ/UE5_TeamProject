// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterSelectWidget.h"

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct(); 
}

bool UCharacterSelectWidget::SetCharacterClassName(ECharacterClass::type type)
{
	//if (!type) { check(false); return false; }

	FText CharacterClassNameText; 

	switch (type)
	{
	case ECharacterClass::Warrior:
		CharacterClassNameText = FText::FromString(TEXT("Warrior"));
		break; 

	case ECharacterClass::Ranger:
		CharacterClassNameText = FText::FromString(TEXT("Ranger"));
		break;

	case ECharacterClass::Swordman:
		CharacterClassNameText = FText::FromString(TEXT("Swordman"));
		break; 

	case ECharacterClass::Spearman:
		CharacterClassNameText = FText::FromString(TEXT("Spearman"));
		break; 

	}

	CharacterClassName->SetText(CharacterClassNameText); 

	return true; 
}
