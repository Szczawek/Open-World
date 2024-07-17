// Fill out your copyright notice in the Description page of Project Settings.


#include "../Cars/Car.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
    BoxComponent->SetSimulatePhysics(true);
    RootComponent = BoxComponent;
    VehicleMovement = CreateDefaultSubobject<UChaosWheeledVehicleMovementComponent>(TEXT("Vehicle Movement"));

    //FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Movement"));
    CarComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Car component"));
    CarComponent->SetupAttachment(BoxComponent);
    ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Third Person Arm"));
    FirstPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FPS Spring Arm"));
    FrontSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Front Spring Arm"));
    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
    ThirdPersonCamera->SetActive(true);
    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS Camera"));
    FirstPersonCamera->SetActive(false);
    FrontCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Font Camera"));
    FrontCamera->SetActive(false);
    ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);
    FirstPersonCamera->SetupAttachment(FirstPersonSpringArm, USpringArmComponent::SocketName);
    FrontCamera->SetupAttachment(FrontSpringArm, USpringArmComponent::SocketName);
    ThirdPersonSpringArm->SetupAttachment(CarComponent);
    FirstPersonSpringArm->SetupAttachment(CarComponent);
    FrontSpringArm->SetupAttachment(CarComponent);
    //FloatingPawnMovement->MaxSpeed = 100.0f;
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
        if (UEnhancedInputLocalPlayerSubsystem* InputSystems = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
            InputSystems->AddMappingContext(InputsController,0);
        }
    }

    if (CarWidgetClass) {
        CarWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), CarWidgetClass);
        CarWidget->AddToViewport();
    }
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);;

    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, FString::Printf(TEXT("3%f"), Speed));
    //if (!bIsCarMoving && Speed > MinSpeed) {
    //    const FRotator Rotation = Controller->GetControlRotation();
    //    const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
    //    const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    //    const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    //    //AddMovementInput(RightVector, RightMovementVector);
    //    AddMovementInput(ForwardVector, ForwardMovementVector);
    //    

    //}



    //if (!bIsCarMoving && Speed > MinSpeed) {
    //    Speed -= 100.0f * DeltaTime;
    //    SlowDownMovement(Speed);
    //}
    //if (bIsCarMoving && Speed < MaxSpeed) {
    //    if (Speed > NextGearSpeed) {
    //        Gear++;
    //        NextGearSpeed += Speed;
    //    }
    //    Speed += 100.f * DeltaTime * Gear;
    //    HigherSpeed(Speed);
    //}
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(GasAction, ETriggerEvent::Triggered, this, &ACar::MoveForward);
        EnhancedInputComponent->BindAction(GasAction, ETriggerEvent::Completed, this, &ACar::StopMoving);
        EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &ACar::Brake);
        EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &ACar::RelaseBrake);
        EnhancedInputComponent->BindAction(TurnWheelAction, ETriggerEvent::Triggered, this, &ACar::TurnWheel);
        EnhancedInputComponent->BindAction(LockAction, ETriggerEvent::Triggered, this, &ACar::Lock);
        EnhancedInputComponent->BindAction(ViewModeAction, ETriggerEvent::Triggered, this, &ACar::SwitchViewMode);
    }

}

void ACar::MoveForward(const FInputActionValue& Value)
{
    if (!bIsCarMoving) bIsCarMoving = true;
    const float MovementVector = Value.Get<float>();
    VehicleMovement->SetThrottleInput(MovementVector);
    //const FRotator Rotation = Controller->GetControlRotation();
    //const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
    //const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    //AddMovementInput(ForwardVector, MovementVector.Y);
    //GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, FString::Printf(TEXT("Movement Vector X: %s"),ForwardVector.ToString ));
    //ForwardMovementVector = MovementVector.Y;
}

void ACar::StopMoving()
{
    if (bIsCarMoving) bIsCarMoving = false;
}

void ACar::TurnWheel(const FInputActionValue& Value)
{
    if (!bIsCarMoving && Speed <= 0.0f) return;
    const FVector2D MovementVector = Value.Get<FVector2D>();
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
    const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * 10.0f;
    AddMovementInput(RightVector, MovementVector.X);
    if (Speed <= 100.0f) return;
    FRotator CarRotation = GetActorRotation();
    CarRotation.Yaw += MovementVector.X;
    RightMovementVector = MovementVector.X;
    SetActorRelativeRotation(CarRotation);
}

void ACar::Brake()
{
    /*if (!bIsCarHasActiveBrake) bIsCarHasActiveBrake = true;
    if (Speed > 0.0f) {
            if (Speed < 100.0f) {
                SlowDownMovement(Speed);
                Speed = 0.0f;
                return;
            } 
            SlowDownMovement(100.0f);
            Speed -= 100.0f;
    }*/
}

void ACar::RelaseBrake()
{
    if (bIsCarHasActiveBrake) bIsCarHasActiveBrake = false;
}

void ACar::Lock(const FInputActionValue& Value)
{
    //const FVector2D MovementVector = Value.Get<FVector2D>();
    //const FRotator Rotator(0.0f, MovementVector.Y, MovementVector.X);
    //ThirdPersonSpringArm->SetRelativeRotation(Rotator);
    //AddControllerYawInput(MovementVector.X);
    //AddControllerPitchInput(MovementVector.Y * -1);
}

void ACar::SwitchViewMode()
{
    if (ThirdPersonCamera->IsActive()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("1"));
        ThirdPersonCamera->SetActive(false);
        FirstPersonCamera->SetActive(true);
    } else if(FirstPersonCamera->IsActive()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("2"));
        FirstPersonCamera->SetActive(false);
        FrontCamera->SetActive(true);
    } else if(FrontCamera->IsActive()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("3"));
        FrontCamera->SetActive(false);
        ThirdPersonCamera->SetActive(true);
    }
}

