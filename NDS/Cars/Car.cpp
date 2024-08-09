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
    FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Movement"));

    BoxComponent->SetSimulatePhysics(true);
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
    if (BoxComponent) {
        BoxComponent->OnComponentHit.AddDynamic(this, &ACar::Collision);
    }
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsCarMoving && Speed > 0.0f && !bIsCarReverseMoving) {
        SlowDownMovement(100.0f * DeltaTime);
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
        FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(ForwardVector, ForwardMovementValue);
}

    if (bIsCarMoving && Speed < MaxSpeed) {
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
        EnhancedInputComponent->BindAction(TurnWheelAction, ETriggerEvent::Completed, this, &ACar::StopWheel);
        EnhancedInputComponent->BindAction(LockAction, ETriggerEvent::Triggered, this, &ACar::Lock);
        EnhancedInputComponent->BindAction(ViewModeAction, ETriggerEvent::Triggered, this, &ACar::SwitchViewMode);
    }

}

void ACar::MoveForward(const FInputActionValue& Value)
{
    if (bIsCarHasActiveBrake || bIsCarReverseMoving || !bHasFuel) return;
    if (Speed > 0.0f && !bIsCarMoving && !bIsCarReverseMoving) {
        if (Speed - 20.0f < 0.0f) return ResetSpeed();
            return SlowDownMovement(10.0f);        
    }
    if (!bIsCarMoving) bIsCarMoving = true;
    const FVector2D MovementVector = Value.Get<FVector2D>();
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
    const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardVector, MovementVector.Y);
    ForwardMovementValue = MovementVector.Y;
}

void ACar::StopMoving()
{
    if (bIsCarMoving) bIsCarMoving = false;
}

void ACar::TurnWheel(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();
    float RateValue = GetWorld()->GetDeltaSeconds();
    float Right = MovementVector.X * RateValue * 0.01f;
    RightMovementValue += Right * 100;

    if (!bIsCarMoving && Speed <= 10.0f || !bIsCarReverseMoving && Speed <= 10.0f) return;

    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
    FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(RightVector, Right);
    FRotator CarRotation = GetActorRotation();
    float RotateBy = MovementVector.X * RateValue * 12.f;

    if (bIsCarReverseMoving || FMath::IsNegative(ForwardMovementValue)) {
        RotateBy *= -1.0f;
    }

    AddControllerYawInput(RotateBy);
    CarRotation.Yaw += RotateBy * 2.5f;
    SetActorRotation(CarRotation);

}

void ACar::StopWheel()
{
    if (RightMovementValue != 0.0f) {
        RightMovementValue = 0.0f;
    }
}

void ACar::ReverseGear(const FInputActionValue& Value)
{
    if (bIsCarHasActiveBrake || !bHasFuel) return;
    if (bIsCarMoving) bIsCarMoving = false;
    if (Speed > 0.0f && !bIsCarReverseMoving) {
        if (Speed - 20.0f < 0.0f) return ResetSpeed();
           return SlowDownMovement(10.0f);
    }

    if (!bIsCarReverseMoving) bIsCarReverseMoving = true;

    if (Speed <= 400.0f) {
        HigherSpeed(5.0f);
    }

    const FVector2D MovementVector = Value.Get<FVector2D>();
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotator(0.0f, Rotation.Yaw, 0.0f);
    const FVector BackVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
    AddMovementInput(BackVector, MovementVector.Y);
    ForwardMovementValue = MovementVector.Y;

}

void ACar::RelaseReverseGear()
{
    if (bIsCarReverseMoving) bIsCarReverseMoving = false;
}

void ACar::HandBrake()
{
    if (bIsCarMoving) bIsCarMoving = false;
    if (bIsCarReverseMoving) bIsCarReverseMoving = false;
    if (Speed > 0.0f) {
        if (Speed < 100.0f) return ResetSpeed();
            SlowDownMovement(5.0f);
    }
}

void ACar::RelaseHandBrake()
{
    if (bIsCarHasActiveBrake) bIsCarHasActiveBrake = false;
}

void ACar::Collision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

    //GROUND COLLISION

    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("COLISIO"));
    //    // Ignore collisions with the ground or with minimal impact
    //    if (OtherActor->ActorHasTag(FName("Ground"))) return;
    //   
    //if (Speed > 0.0f) {
    //    ResetSpeed();
    //}
}

void ACar::Lock(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();
    FRotator ArmRotation = ThirdPersonSpringArm->GetRelativeRotation();
    ArmRotation.Yaw += MovementVector.X;
    ThirdPersonSpringArm->SetRelativeRotation(ArmRotation);
}


void ACar::SwitchViewMode()
{
    if (ThirdPersonCamera->IsActive()) {
        ThirdPersonCamera->SetActive(false);
        FirstPersonCamera->SetActive(true);

    } else if(FirstPersonCamera->IsActive()) {
        FirstPersonCamera->SetActive(false);
        FrontCamera->SetActive(true);

    } else if(FrontCamera->IsActive()) {
        FrontCamera->SetActive(false);
        ThirdPersonCamera->SetActive(true);

    }
}

