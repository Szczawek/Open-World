// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "../NormalGameMode.h"
#include "EndScreen.generated.h"

/**
 * 
 */
UCLASS()
class NDS_API UEndScreen : public UUserWidget
{
	GENERATED_BODY()

protected: 
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> EndButton;
    
    UFUNCTION()
    void OnEndButtonClicked();
	
    UPROPERTY()
    ANormalGameMode* GameMode;

};
