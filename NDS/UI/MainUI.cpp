#include "../UI/MainUI.h"

void UMainUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (AFPSPlayer* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<AFPSPlayer>()) {
        PlayerCharacter->StatsDelegate.AddDynamic(this, &UMainUI::UpdateStats);
    }

    if (Budget) {
        Budget->SetText(FText::FromString(TEXT("0")));
    }
    if (HealthBar) {
        HealthBar->SetPercent(100.0f);
    }
    if (StaminaBar) {
        StaminaBar->SetPercent(100.0f);
    }

}

void UMainUI::UpdateStats(float Value,FString Type)
{
    if (Type == TEXT("Health")) {
        HealthBar->SetPercent(Value);
    }
    if (Type == TEXT("Stamina")) {
        StaminaBar->SetPercent(Value);
    }
    if (Type == TEXT("Coin")) {
        FString BudgetAmount = FString::SanitizeFloat(Value);
        Budget->SetText(FText::FromString(BudgetAmount));
    }
    
}


