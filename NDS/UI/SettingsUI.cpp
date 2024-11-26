// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/SettingsUI.h"

void USettingsUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (MenuWidgetClass) {
        MenuWidget = CreateWidget<UUserWidget>(this, MenuWidgetClass);
    }

    if (AFPSPlayer* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<AFPSPlayer>()) {
        PlayerCharacter->OpenMenuDelegate.AddDynamic(this, &USettingsUI::OpenMenu);
    }
}

void USettingsUI::OpenMenu()
{

    
}

void USettingsUI::CloseMenu()
{
    RemoveFromParent();
}
