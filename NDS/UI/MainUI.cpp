// Fill out your copyright notice in the Description page of Project Settings.
#include "../UI/MainUI.h"

void UMainUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (AFPSPlayer* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<AFPSPlayer>()) {
        PlayerCharacter->EndGameDelegate.AddDynamic(this, &UMainUI::SetEndGameWidget);
        PlayerCharacter->MenuDelegate.AddDynamic(this, &UMainUI::RemoveFromScreen);
        PlayerCharacter->StatsDelegate.AddDynamic(this, &UMainUI::UpdateStats);
    }
    if (HealthBar) {
        HealthBar->SetPercent(100.0f);
    }
    if (StaminaBar) {
        StaminaBar->SetPercent(100.0f);
    }

}

void UMainUI::SetEndGameWidget()
{
    RemoveFromParent();
    if (EndWidgetClass) {
        EndWidget = CreateWidget<UUserWidget>(this, EndWidgetClass);
        EndWidget->AddToViewport();
    }
}

void UMainUI::RemoveFromScreen()
{
    RemoveFromParent();
}

void UMainUI::UpdateStats(float Value,FString Type)
{
  
 
    if (Type == TEXT("Health")) {
        HealthBar->SetPercent(Value);
    }
    if (Type == TEXT("Stamina")) {
        StaminaBar->SetPercent(Value);
    }
    if (Type == TEXT("Coin")) {
     
    }
    
}


