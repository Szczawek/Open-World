// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include <Components/TextBlock.h>
#include "../NormalGameMode.h"
#include "StartMenu.generated.h"

UCLASS()
class NDS_API UStartMenu : public UUserWidget
{
	GENERATED_BODY()

protected: 
    virtual void NativeConstruct() override;
    
public: 
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> StartButton;
       
    UFUNCTION()
    void OnStartButtonClicked();

    UPROPERTY()
    APlayerController* Player;

    UPROPERTY(EditAnywhere, Category = "Widget")
    TSubclassOf<UUserWidget> GameWidgetClass;

    UPROPERTY()
    UUserWidget* GameWidget;

    UPROPERTY()
    ANormalGameMode* GameMode;
};
