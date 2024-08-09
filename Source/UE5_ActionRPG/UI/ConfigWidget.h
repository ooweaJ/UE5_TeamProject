// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfigWidget.generated.h"

class UTextBlock; 
class UButton; 


UENUM()
enum class EConfigName : uint8
{
	Texture, 
	AntiAliasing, 
	Shadow, 
	Shading, 
	Effect,
	GlobalIllumination, 
};


UENUM()
enum class EConfigQuality : uint8
{
	lowest, 
	low, 
	medium,
	high,
	highest, 
	_End
};

UCLASS()
class UE5_ACTIONRPG_API UConfigWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override; 

	virtual void NativeDestruct() override; 

public:
	void SetConfigNameText(EConfigName ConfigName); 

	void SetConfigQualityText(EConfigQuality ConfigQuality); 

	void SetConfigNameIndex(uint8 InIndex) { ConfigNameIndex = InIndex; }

	void SetConfigQualityIndex(uint8 InIndex) { ConfigQualityIndex = InIndex; }

	uint8 GetConfigNameIndex() const { return ConfigNameIndex; }

	uint8 GetConfigQualityIndex() const { return ConfigQualityIndex; }
public:
	UFUNCTION()
	void OnConfigMinusButtonClicked(); 

	UFUNCTION()
	void OnConfigPlusButtonClicked(); 

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ConfigNameTextBlock; 

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ConfigMinusButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ConfigQualityTextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ConfigPlusButton;


private:
	uint8 ConfigNameIndex; 

	uint8 ConfigQualityIndex = 3; 
};
