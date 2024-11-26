// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "UI.generated.h"

/**
 * 
 */
UCLASS()
class NDS_API UUI : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:

    UPROPERTY(EditAnywhere)
    UCanvasPanel* Canvas;

    UPROPERTY(EditAnywhere, Category = "User Interfaces")
    TSubclassOf<UUserWidget> GameClass;
    
    UPROPERTY(EditAnywhere, Category = "User Interfaces")
    TSubclassOf<UUserWidget> EndGameClass;
    
    UPROPERTY(EditAnywhere, Category = "User Interfaces")
    TSubclassOf<UUserWidget> StartGameClass;
    
    UPROPERTY()
    UUserWidget* StartGame;

    UPROPERTY(EditAnywhere, Category = "User Interfaces")
    TSubclassOf<UUserWidget> SettingsClass;


};
