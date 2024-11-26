// Fill out your copyright notice in the Description page of Project Settings.


#include "../UI/UI.h"

void UUI::NativeConstruct()
{
    Super::NativeConstruct();
    if (UWidget* RootWidget = GetRootWidget()) {

        Canvas = Cast<UCanvasPanel>(RootWidget);
    }


    if (StartGameClass) {
        StartGame = CreateWidget<UUserWidget>(this, StartGameClass);
        Canvas->AddChild(StartGame);
    }
}
