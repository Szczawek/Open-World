// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/BoxComponent.h>
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"
#include <GameFramework/FloatingPawnMovement.h>
#include "../../../../../Engine/Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/ChaosWheeledVehicleMovementComponent.h"
#include "Car.generated.h"
UCLASS()
class NDS_API ACar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(BlueprintReadWrite, Category = "Car Stats")
    UChaosWheeledVehicleMovementComponent* VehicleMovement;

    UPROPERTY(EditAnywhere, Category = "Car")
    USkeletalMeshComponent* CarComponent;

    UPROPERTY(EditAnywhere, Category = "Box Component")
    UBoxComponent* BoxComponent;

    //Vehicle Lock Actions 
    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent* ThirdPersonCamera;

    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent* FirstPersonCamera;

    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent* FrontCamera;

    UPROPERTY(EditAnywhere, Category = "Camera")
    USpringArmComponent* ThirdPersonSpringArm;

    UPROPERTY(EditAnywhere, Category = "Camera")
    USpringArmComponent* FirstPersonSpringArm;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* LockAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* ViewModeAction;

    // Vechicle Movement 
    UPROPERTY(EditDefaultsOnly, Category = "Camera")
    USpringArmComponent* FrontSpringArm;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputMappingContext* InputsController;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* GasAction;
    
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* BrakeAction;

    UPROPERTY(EditAnyWhere, Category = "Input")
    UInputAction* TurnWheelAction;

 

    bool bIsCarMoving = false;
    bool bIsCarHasActiveBrake = false;

    float ForwardMovementVector = 0.0f;
    float RightMovementVector = 0.0f;

    void MoveForward(const FInputActionValue& Value);
    void StopMoving();
    void TurnWheel(const FInputActionValue& Value);
    void Lock(const FInputActionValue& Value);

    void Brake();
    void RelaseBrake();
    //void SlowDownMovement(float Value) {
    //    FloatingPawnMovement->MaxSpeed -= Value;
    //}
    //void HigherSpeed(float Value) {
    //    FloatingPawnMovement->MaxSpeed += Value;
    //}

    void SwitchViewMode();

    float Rate = 5.0f;
    float Timmer = 0.0f;

    float Gear = 1;
    float NextGearSpeed = 200.f;


    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float Speed = 08.0f;
    float MinSpeed = 0.0f;
    float MaxSpeed = 1800.0f;

    UPROPERTY(EditAnywhere, Category = "Widget")
    TSubclassOf<UUserWidget> CarWidgetClass;

    UPROPERTY()
    UUserWidget* CarWidget;
};
