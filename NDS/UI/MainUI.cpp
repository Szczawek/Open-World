// Fill out your copyright notice in the Description page of Project Settings.
#include "../UI/MainUI.h"

void UMainUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (AFPSPlayer* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<AFPSPlayer>()) {
        PlayerCharacter->EndGameDelegate.AddDynamic(this, &UMainUI::SetEndGameWidget);
        PlayerCharacter->MenuDelegate.AddDynamic(this, &UMainUI::RemoveFromScreen);
    }
 
    if (Budget) {
        Budget->SetText(FText::FromString(TEXT("Budget")));
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


