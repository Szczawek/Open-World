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
    FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Movement"));

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
    FloatingPawnMovement->MaxSpeed = 0.0f;
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
    if (!bIsCarMoving && Speed > MinSpeed && !bIsCarReverseMoving) {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
        const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        //AddMovementInput(RightVector, RightMovementVector);
        AddMovementInput(ForwardVector, ForwardMovementVector);
    }

    if (!bIsCarMoving && Speed > MinSpeed && !bIsCarReverseMoving) {
       /* if (Speed < NextGearSpeed) {
            if (NextGearSpeed - Speed > 0.0f) {
            NextGearSpeed -= Speed;
            }
            else {
                NextGearSpeed = 0.0f;
            }
            Gear--;
        }*/
        SlowDownMovement(100.0f * DeltaTime);
    }
    if (bIsCarMoving && Speed < MaxSpeed) {
  /*      if (Speed > NextGearSpeed) {
            Gear++;
            NextGearSpeed += Speed;
        }*/
        HigherSpeed(100.f * DeltaTime * 2);
    }
}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(GasAction, ETriggerEvent::Triggered, this, &ACar::MoveForward);
        EnhancedInputComponent->BindAction(GasAction, ETriggerEvent::Completed, this, &ACar::StopMoving);
        EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &ACar::ReverseGear);
        EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &ACar::RelaseReverseGear);
        EnhancedInputComponent->BindAction(HandBrakeAction, ETriggerEvent::Triggered, this, &ACar::HandBrake);
        EnhancedInputComponent->BindAction(HandBrakeAction, ETriggerEvent::Completed, this, &ACar::RelaseHandBrake);
        EnhancedInputComponent->BindAction(TurnWheelAction, ETriggerEvent::Triggered, this, &ACar::TurnWheel);
        EnhancedInputComponent->BindAction(LockAction, ETriggerEvent::Triggered, this, &ACar::Lock);
        EnhancedInputComponent->BindAction(ViewModeAction, ETriggerEvent::Triggered, this, &ACar::SwitchViewMode);
    }

}

void ACar::MoveForward(const FInputActionValue& Value)
{

    if (Speed > 0.0f && !bIsCarMoving) {
        UE_LOG(LogTemp, Warning, TEXT("1"));
        if (Speed - 20.0f < 0.0f) {
            Speed = 0.0f;
            FloatingPawnMovement->MaxSpeed = 0.0f;
        }
        else {
            SlowDownMovement(20);
        }
        return;
    }
    if (!bIsCarMoving) bIsCarMoving = true;
    UE_LOG(LogTemp, Warning, TEXT("2"));
    const FVector2D MovementVector = Value.Get<FVector2D>();
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
    const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardVector, MovementVector.Y);
    ForwardMovementVector = MovementVector.Y;
}

void ACar::StopMoving()
{
    if (bIsCarMoving) bIsCarMoving = false;
}

void ACar::TurnWheel(const FInputActionValue& Value)
{
    //if (!bIsCarMoving && Speed <= 0.0f || !bIsCarReverseMoving && Speed <= 0.0f) return;
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

void ACar::ReverseGear(const FInputActionValue& Value)
{
    if (bIsCarMoving) bIsCarMoving = false;
    if (Speed > 0.0f && !bIsCarReverseMoving) {
        if (Speed - 20.0f < 0.0f) {
            Speed = 0.0f;
            FloatingPawnMovement->MaxSpeed = 0.0f;
        }
        else {
        SlowDownMovement(20);
        }
        return;
    }

    if (!bIsCarReverseMoving) {
        bIsCarReverseMoving = true;
        HigherSpeed(400.0f);
    }
    const FVector2D MovementVector = Value.Get<FVector2D>();
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotator(0.0f, Rotation.Yaw, 0.0f);
    const FVector BackVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
    AddMovementInput(BackVector, MovementVector.Y);
    ForwardMovementVector = MovementVector.Y;

}

void ACar::RelaseReverseGear()
{
    if (bIsCarReverseMoving) bIsCarReverseMoving = false;
}

void ACar::HandBrake()
{
    if (!bIsCarHasActiveBrake) bIsCarHasActiveBrake = true;
    if (Speed > 0.0f) {
            if (Speed < 100.0f) {
                FloatingPawnMovement->MaxSpeed = 0;
                Speed = 0.0f;
                return;
            } 
            SlowDownMovement(100.0f);
    }
}

void ACar::RelaseHandBrake()
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

