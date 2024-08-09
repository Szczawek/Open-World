// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/SettingsUI.h"

void USettingsUI::NativeConstruct()
{
    Super::NativeConstruct();
}

void USettingsUI::OpenMenu()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("1"));
}

void USettingsUI::CloseMenu()
{

}
