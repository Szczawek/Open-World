#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "../Player/FPSPlayer.h"
#include "Components/ProgressBar.h"
#include "MainUI.generated.h"


UCLASS()
class NDS_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

protected: 
    virtual void NativeConstruct() override;

public:

    UFUNCTION()
    void UpdateStats(float Value,FString Type);

    UPROPERTY(meta  = (BindWidget))
    UTextBlock* Budget;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* StaminaBar;


};
