// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_ProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class UE5_ACTIONRPG_API UUI_ProgressBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BindWidget))
	class UImage* ProgressBarImage;
};
