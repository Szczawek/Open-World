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
    
    UPROPERTY(EditAnywhere, Category = "Stats")
    UFloatingPawnMovement* FloatingPawnMovement;

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
    
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* BrakeAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* HandBrakeAction;

    UPROPERTY(EditAnyWhere, Category = "Input")
    UInputAction* TurnWheelAction;
    

    //Car Logic
    bool bHasFuel = true;
    bool bIsCarMoving = false;
    bool bIsCarReverseMoving = false;
    bool bIsCarHasActiveBrake = false;
  
    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float ForwardMovementValue = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float RightMovementValue = 0.0f;

    void MoveForward(const FInputActionValue& Value);
    void StopMoving();
    void TurnWheel(const FInputActionValue& Value);
    void StopWheel();
    void Lock(const FInputActionValue& Value);

    void ReverseGear(const FInputActionValue& Value);
    void RelaseReverseGear();

    void HandBrake();
    void RelaseHandBrake();

    void SlowDownMovement(float Value) {
        Speed -= Value;
        FloatingPawnMovement->MaxSpeed -= Value;
    }
    void HigherSpeed(float Value) {
        Speed += Value;
        FloatingPawnMovement->MaxSpeed += Value;
    }

    void ResetSpeed() {
        Speed = 0.0f;
        FloatingPawnMovement->MaxSpeed = 0.0f;
    }

    UFUNCTION()
    void Colision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

    /// Car Stats
    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float Speed = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Stats")
    float MaxSpeed = 1800.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float Fuel = 1.0f;



    void SwitchViewMode();

    UPROPERTY(EditAnywhere, Category = "Widget")
    TSubclassOf<UUserWidget> CarWidgetClass;

    UPROPERTY()
    UUserWidget* CarWidget;
};
