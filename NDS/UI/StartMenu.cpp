// Fill out your copyright notice in the Description page of Project Settings.


#include "./StartMenu.h"
#include <Kismet/GameplayStatics.h>

void UStartMenu::NativeConstruct()
{
    Super::NativeConstruct();
    Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (StartButton) {
        StartButton->OnClicked.AddDynamic(this, &UStartMenu::OnStartButtonClicked);
    }
}

void UStartMenu::OnStartButtonClicked()
{
    if (Player) {
        Player->bShowMouseCursor = false;
        if (IsInViewport()) {
            RemoveFromParent();
            FInputModeGameOnly PrevInputMode;
            Player->SetInputMode(PrevInputMode);
            if (GameWidgetClass) {
                GameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass);
                GameWidget->AddToViewport();
            }

        }
    }
}
