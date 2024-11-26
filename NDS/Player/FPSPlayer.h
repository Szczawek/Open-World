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

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenMainWidgetDelegate);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenMenuDelegate);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStatsDelegate, float, Value, FString, Type);

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
    UPROPERTY()
    FStatsDelegate StatsDelegate;
    UPROPERTY()
    FOpenMainWidgetDelegate OpenMainWidgetDelegate;

    UPROPERTY()
    FOpenMenuDelegate OpenMenuDelegate;

    UPROPERTY(EditAnywhere, Category = "Mesh")
    USkeletalMeshComponent* MeshComponent;
    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent* ThirdPersonCamera;

    UPROPERTY(EditDefaultsOnly, Category = "Camera")
    UCameraComponent* FirstPersonCamera;

    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent* BackwardCamera;

    UPROPERTY(EditDefaultsOnly, Category = "Rack") 
    USpringArmComponent* FirstPersonArm;

    UPROPERTY(EditDefaultsOnly, Category = "Rack")
    USpringArmComponent* BackwardSpringArm;

    UPROPERTY(EditDefaultsOnly, Category = "Rack")
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
    
    UPROPERTY(EditAnywhere, Category = "User Interface")
    TSubclassOf<UUserWidget> UserInterfaceClass;

    UPROPERTY()
    UUserWidget* UserInterface;

        //UPROPERTY(EditAnywhere, Category = "Widget")
        //TSubclassOf<UUserWidget>  SettingsWidgetClass;

       /* UPROPERTY()
        UUserWidget* SettingsWidget;*/

    bool bMenuIsOpened = false;

    UFUNCTION()
    void TakeWeapon();

    //UPROPERTY()
    //AWeapon* EquipedWeapon;

    void EndGame();

    UFUNCTION()
    void SetSpeedLimit(const float Value) {
        MovementComponent->MaxWalkSpeed = Value;
    };

    UFUNCTION()
    void UpdateStamina(const float Value, const FString& Type) {
        if (Value == 0.f || Type.IsEmpty()) return;
        float UpdatedStamina = Stats.Stamina;   
        if (Type == TEXT("add")) {
            UpdatedStamina += Value;
        }
        if (Type == TEXT("reduce")) {
            UpdatedStamina -= Value;
        }
        if (StatsDelegate.IsBound()) {
            StatsDelegate.Broadcast(UpdatedStamina, "Stamina");
        }
        Stats.Stamina = UpdatedStamina;
    }

    UFUNCTION()
    void PlayerHoldWeapon() {
        PlayerStatus.bIsPLayerHoldsWeapon = true;
    }

    UFUNCTION()
    void AddPoint(const int32 Value = 1) {
        int32 UpdatedBudget = Stats.Points += Value;

        if (StatsDelegate.IsBound()) {
        
            StatsDelegate.Broadcast(UpdatedBudget, "Coin");

        }
        Stats.Points = UpdatedBudget;
    }

    UFUNCTION()
    void ApplyDemage(const float Value) {
        float UpdatedHealth = Stats.Health -= Value;
        Stats.Health = UpdatedHealth;;
        if (StatsDelegate.IsBound()) {
            StatsDelegate.Broadcast(UpdatedHealth,"Health");
        }
    };
};
