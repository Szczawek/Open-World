// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Player/FPSPlayer.h"
#include "SettingsUI.generated.h"

/**
 * 
 */
UCLASS()
class NDS_API USettingsUI : public UUserWidget
{
	GENERATED_BODY()

private: 
    virtual void NativeConstruct() override;

public: 
    void OpenMenu();
    void CloseMenu();



    UPROPERTY()
    UUserWidget* MenuWidget;

    UPROPERTY()
    TSubclassOf<UUserWidget> MenuWidgetClass;

};
