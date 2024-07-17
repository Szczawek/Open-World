// Fill out your copyright notice in the Description page of Project Settings.
#include "../UI/MainUI.h"

void UMainUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (AFPSPlayer* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<AFPSPlayer>()) {
        PlayerCharacter->EndGameDelegate.AddDynamic(this, &UMainUI::RemovePreviouseWidget);
    }
 
    if (Budget) {
        Budget->SetText(FText::FromString(TEXT("Budget")));
    }
}

void UMainUI::RemovePreviouseWidget()
{
    RemoveFromParent();
    if (EndWidgetClass) {
        EndWidget = CreateWidget<UUserWidget>(this, EndWidgetClass);
        EndWidget->AddToViewport();
    }
}


