// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ConfigMenuWidget.h"
#include "UI/ConfigWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Scalability.h"

void UConfigMenuWidget::NativeConstruct()
{
	Super::NativeConstruct(); 

	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddDynamic(this, &UConfigMenuWidget::OnApplyButtonClicked); 
	}

	if (GoBackButton)
	{
		GoBackButton->OnClicked.AddDynamic(this, &UConfigMenuWidget::OnGoBackButtonClicked); 
	}

	InitVerticalBox(); 
	
}

void UConfigMenuWidget::NativeDestruct()
{
	Super::NativeDestruct(); 

	if (ApplyButton)
	{
		ApplyButton->OnClicked.RemoveDynamic(this, &UConfigMenuWidget::OnApplyButtonClicked);
	}

	if (GoBackButton)
	{
		GoBackButton->OnClicked.RemoveDynamic(this, &UConfigMenuWidget::OnGoBackButtonClicked);
	}

}

void UConfigMenuWidget::InitVerticalBox()
{
	const TArray<UWidget*>& ConfigChildren = ConfigMenuVerticalBox->GetAllChildren();
	const uint8 NumChildren = ConfigChildren.Num(); 

	for (uint8 i = 0; i < NumChildren; ++i)
	{
		if (UConfigWidget* Config = Cast<UConfigWidget>(ConfigChildren[i]))
		{
			Config->SetConfigNameText(static_cast<EConfigName>(i)); 
			Config->SetConfigQualityText(EConfigQuality::high); 
			Config->SetConfigNameIndex(i); 
			Config->SetConfigQualityIndex(static_cast<uint8>(EConfigQuality::high)); 
		}
	}
}

void UConfigMenuWidget::OnApplyButtonClicked()
{
	const TArray<UWidget*>& ConfigChildren = ConfigMenuVerticalBox->GetAllChildren();
	const uint8 NumChildren = ConfigChildren.Num();

	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();

	for (uint8 i = 0; i < NumChildren; ++i)
	{
		if (UConfigWidget* Config = Cast<UConfigWidget>(ConfigChildren[i]))
		{
			const uint8& CurrentQualityIndex = Config->GetConfigQualityIndex(); 
			const uint8& CurrentNameIndex = Config->GetConfigNameIndex(); 
			const EConfigName& ConfigName = static_cast<EConfigName>(CurrentNameIndex); 


			switch (ConfigName)
			{
			case EConfigName::Texture:
			{
				QualityLevels.TextureQuality = CurrentQualityIndex;
				break;
			}
			case EConfigName::AntiAliasing:
			{
				QualityLevels.AntiAliasingQuality = CurrentQualityIndex; 
				break;
			}
			case EConfigName::Shadow:
			{
				QualityLevels.ShadowQuality = CurrentQualityIndex; 
				break; 
			}
			case EConfigName::Shading:
			{
				QualityLevels.ShadingQuality = CurrentQualityIndex; 
				break; 
			}
			case EConfigName::Effect:
			{
				QualityLevels.EffectsQuality = CurrentQualityIndex; 
				break;
			}
			case EConfigName::GlobalIllumination:
			{
				QualityLevels.GlobalIlluminationQuality = CurrentQualityIndex; 
				break; 
			}
			}
		}
	}
	Scalability::SetQualityLevels(QualityLevels);
}

void UConfigMenuWidget::OnGoBackButtonClicked()
{
	UWidget* ParentWidget = GetParent(); 

	if (UWidgetSwitcher* ParentSwitcher = Cast<UWidgetSwitcher>(ParentWidget))
	{
		ParentSwitcher->SetActiveWidgetIndex(0); 
	}
}
