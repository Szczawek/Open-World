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

    void SetSpeedLimit(const float Value) {
        MovementComponent->MaxWalkSpeed = Value;
    };

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

    float NormalSpeed = 600.0f;
    float SprintSpeed = 1000.0f;
    float SneakingSpeed = 400.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Character Stats")
    float Health = 1.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Character Stats")
    float Stamina = 1.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Character Stats")
    float Points = 0.0f;

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

    void AddPoint() {
        Points += 1.0f;
    }
    void ApplyDemage();
};
