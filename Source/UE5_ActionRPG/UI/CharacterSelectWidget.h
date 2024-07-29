// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CharacterSelectWidget.generated.h"

namespace ECharacterClass
{
	enum type
	{
		Warrior, 
		Ranger, 
		Swordman, 
		Spearman, 
		_End 
	};
}
UCLASS()
class UE5_ACTIONRPG_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	bool SetCharacterClassName(ECharacterClass::type type);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* CharacterClassName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* CharacterImage;
};
