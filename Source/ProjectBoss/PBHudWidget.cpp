// Fill out your copyright notice in the Description page of Project Settings.


#include "PBHudWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPBHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(FName("ProgressBar_HP")));
	HPTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName("TextBlock_HP")));
	HPRegenTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName("TextBlock_HPRegen")));

	StaminaBar = Cast<UProgressBar>(GetWidgetFromName(FName("ProgressBar_Stamina")));
	StaminaTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName("TextBlock_Stamina")));
	StaminaRegenTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName("TextBlock_StaminaRegen")));
}

void UPBHudWidget::UpdateHPWidget()
{
	HPBar->SetPercent(HP / MaxHP);
	FString String = FString::Printf(TEXT("%.1f / %.1f"), MaxHP, HP);
	HPTextBlock->SetText(FText::FromString(String));
}

void UPBHudWidget::UpdateStaminaWidget()
{
	StaminaBar->SetPercent(Stamina / MaxStamina);
	FString String = FString::Printf(TEXT("%.1f / %.1f"), MaxStamina, Stamina);
	StaminaTextBlock->SetText(FText::FromString(String));
}

void UPBHudWidget::OnMaxHPChanged(float ChangedValue)
{
	MaxHP = ChangedValue;
	UpdateHPWidget();
}

void UPBHudWidget::OnHPChanged(float ChangedValue)
{
	HP = ChangedValue;
	UpdateHPWidget();
}

void UPBHudWidget::OnHPRegenChanged(float ChangedValue)
{
	HPRegen = ChangedValue;
	FString RegenString = FString::Printf(TEXT("+ %.2f"), HPRegen);
	HPRegenTextBlock->SetText(FText::FromString(RegenString));
}

void UPBHudWidget::OnMaxStaminaChanged(float ChangedValue)
{
	MaxStamina = ChangedValue;
	UpdateStaminaWidget();
}

void UPBHudWidget::OnStaminaChanged(float ChangedValue)
{
	Stamina = ChangedValue;
	UpdateStaminaWidget();
}

void UPBHudWidget::OnStaminaRegenChanged(float ChangedValue)
{
	StaminaRegen = ChangedValue;
	FString RegenText = FString::Printf(TEXT("+ %.2f"), StaminaRegen);
	StaminaRegenTextBlock->SetText(FText::FromString(RegenText));
}