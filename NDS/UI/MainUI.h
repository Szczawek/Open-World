#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
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

    UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> Budget;;

    UPROPERTY(EditAnywhere, Category = "Widget")
    TSubclassOf<UUserWidget> EndWidgetClass;

    UPROPERTY()
    UUserWidget* EndWidget;

    UFUNCTION()
    void SetEndGameWidget();

    UFUNCTION()
    void RemoveFromScreen();

    UFUNCTION()
    void UpdateStats(float Value,FString Type);

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* StaminaBar;

   /* UPROPERTY(meta = (BindWidget))
    UTextBlock* CoinAmount;*/
};
