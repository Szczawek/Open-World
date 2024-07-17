// Fill out your copyright notice in the Description page of Project Settings.


#include "./NormalGameMode.h"
#include "Blueprint/UserWidget.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/GameMode.h>

ANormalGameMode::ANormalGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    
}

void ANormalGameMode::BeginPlay()
{
    Super::BeginPlay();
    Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (Player) {
        if (StartWidgetClass) {
            StartWidget = CreateWidget<UUserWidget>(GetWorld(), StartWidgetClass);
            StartWidget->AddToViewport();
            FInputModeUIOnly InputMode;
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            Player->SetInputMode(InputMode);
            Player->bShowMouseCursor = true;
        }
    }
}

void ANormalGameMode::RestartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("SDSDSD"))
}
