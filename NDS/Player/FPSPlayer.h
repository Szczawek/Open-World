// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Camera/CameraComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include <InputMappingContext.h>
#include <InputAction.h>
#include "Blueprint/UserWidget.h"
#include "../Player/PlayerSettings.h"
#include "FPSPlayer.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndGameDelegate);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuDelegate);

UCLASS()
class NDS_API AFPSPlayer : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AFPSPlayer();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public: 
    FPlayerStatus PlayerStatus;
    FMovementSpeed SpeedType;
    FCharacterStats Stats;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY()
    FEndGameDelegate EndGameDelegate;

    UPROPERTY()
    FMenuDelegate MenuDelegate;

    UPROPERTY(EditAnywhere, Category = "Mesh")
    USkeletalMeshComponent* MeshComponent;
    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent* ThirdPersonCamera;
    UPROPERTY(EditAnywhere, Category = "Camera");
    UCameraComponent* FPSCamera;
    UPROPERTY(EditAnywhere)
    USpringArmComponent* SpringArm;


    UPROPERTY(EditAnywhere, Category = "Input")
    UInputMappingContext* PlayerSetting;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MoveAction;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* LockAction;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* FireAction;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* JumpAction;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* SwitchViewModeAction;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* SprintAction;
    UPROPERTY(EditAnyWhere, Category = "Input")
    UInputAction* SneakingAction;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* OpenMenuAction;


    UPROPERTY()
    APlayerController* Player;

    UPROPERTY() 
    UCharacterMovementComponent* MovementComponent;


    void Sneaking();
    void StopSneaking();
    void Jump();
    void StopJumping();
    void Move(const FInputActionValue& Value);
    void StopMoving();
    void Lock(const FInputActionValue& Value);
    void Fire();
    void SwitchViewMode();
    void Sprint();
    void StopSprinting();

    UFUNCTION()
    void OpenMenu();
   
    bool bIsCharacterSprinting = false;
    bool bIsCharacterJumping = false;

    UPROPERTY(EditAnywhere, Category = "Widget")
    TSubclassOf<UUserWidget> EndWidgetClass;

    UPROPERTY()
    UUserWidget* EndWidget;

    UPROPERTY(EditAnywhere, Category = "Widget")
    TSubclassOf<UUserWidget>  SettingsWidgetClass;

    UPROPERTY()
    UUserWidget* SettingsWidget;

    bool bMenuIsOpened = false;

    void EndGame();

    UFUNCTION()
    void SetSpeedLimit(const float Value) {
        MovementComponent->MaxWalkSpeed = Value;
    };

    UFUNCTION()
    void UpdateStamina(const float Value, const FString& Type) {
        if (Value == 0.f || Type.IsEmpty()) return;
        if (Type == TEXT("add")) {
            Stats.Stamina += Value;
        }
        if (Type == TEXT("reduce")) {
            Stats.Stamina -= Value;
        }
    }

    UFUNCTION()
    void AddPoint(const int32 Value = 1) {
        Stats.Points += Value;
    }

    UFUNCTION()
    void ApplyDemage(const float Value) {
        Stats.Health -= Value;
    };
};
