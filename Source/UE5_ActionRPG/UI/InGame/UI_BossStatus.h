// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UI_BossStatus.generated.h"

UCLASS()
class UE5_ACTIONRPG_API UUI_BossStatus : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHP(const float CurrentHP, const float MaxHP);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HPBar = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HPSecond = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* BossName;
private:
	float TargetPercent;
};
