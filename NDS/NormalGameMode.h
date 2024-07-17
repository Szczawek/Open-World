// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Camera/CameraActor.h"
#include "NormalGameMode.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class NDS_API ANormalGameMode : public AGameModeBase
{
	GENERATED_BODY()

public: ANormalGameMode();
protected: 
    virtual void BeginPlay() override;



public:
    UPROPERTY(EditAnywhere, Category = "Start Widget")
    TSubclassOf<UUserWidget> StartWidgetClass;

    UPROPERTY()
    UUserWidget* StartWidget;	

    UPROPERTY()
    APlayerController* Player;

    UPROPERTY(EditAnywhere, Category = "Camera")
   class ACameraActor* StartCamera;


   UFUNCTION()
   void RestartGame();
};
