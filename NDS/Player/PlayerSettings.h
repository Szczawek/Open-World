// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerSettings.generated.h"

USTRUCT(BlueprintType)
struct FMovementSpeed {
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, Category = "Speed")
    float Sneak = 350.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Speed")
    float Normal = 650.f;

    UPROPERTY(BlueprintReadWrite, Category = "Speed")
    float Sprint = 1200.f;
};

USTRUCT(BlueprintType)

struct FPlayerStatus {
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Status")
    bool bIsPlayerSprinting = false;

    UPROPERTY(BlueprintReadWrite, Category = "Status")
    bool bIsPlayerJumping = false;

    UPROPERTY(BlueprintReadWrite, Category = "Status")
    bool bIsPlayerClimbing = false;

    UPROPERTY(VisibleAnywhere, Category = "Status")
    bool bIsPlayerSneaking = false; 

    UPROPERTY(BlueprintReadWrite, Category = "Status")
    bool bIsPlayerDead = false;

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    bool bIsPLayerHoldsWeapon = false;

};

USTRUCT(BlueprintType)
struct FCharacterStats {
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float Health = 1.f;

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float Stamina = 1.f;

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float Budget = 0.f;

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    int32 Points = 0;
};
