// Fill out your copyright notice in the Description page of Project Settings.


#include "../Player/FPSPlayer.h"
#include "EnhancedInputSubsystems.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>



// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);;
    MovementComponent = GetCharacterMovement();
    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
    FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS Camera"));
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    FPSCamera->SetupAttachment(MeshComponent);
    SpringArm->SetupAttachment(RootComponent);
    ThirdPersonCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    MovementComponent->MaxWalkSpeed = NormalSpeed;
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();  
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
        if (UEnhancedInputLocalPlayerSubsystem* InputSystems = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
            InputSystems->AddMappingContext(PlayerSetting, 0);
        }

    }
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Timmer += DeltaTime;
    if (!bIsCharacterSprinting && Stamina < 100.0f && Timmer >= 0.4f) {
        Stamina += 0.1f;
        Timmer = 0.0f;
    }



    if (bIsCharacterSprinting && Timmer > 0.2f) {
        if (Stamina <= 0.0f)
        {
            bIsCharacterSprinting = false;
            SetSpeedLimit(NormalSpeed);
            return;
        }
        Timmer = 0.0f;
        Stamina -= 0.05f;
   
    }
    if (bIsCharacterJumping && CanJump()) {
        bIsCharacterJumping = false;
    }
}


// Called to bind functionality to input
void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Jump);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AFPSPlayer::StopMoving);
        EnhancedInputComponent->BindAction(LockAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Lock);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Fire);
        EnhancedInputComponent->BindAction(SwitchViewModeAction, ETriggerEvent::Triggered, this, &AFPSPlayer::SwitchViewMode);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Sprint);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFPSPlayer::StopSprinting);
        EnhancedInputComponent->BindAction(SneakingAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Sneaking);
        EnhancedInputComponent->BindAction(SneakingAction, ETriggerEvent::Completed, this, &AFPSPlayer::StopSneaking);
    }

}

void AFPSPlayer::Sneaking()
{
    SetSpeedLimit(SneakingSpeed);
}

void AFPSPlayer::StopSneaking()
{
    SetSpeedLimit(NormalSpeed);
}

void AFPSPlayer::Jump()
{
    if (Stamina <= 0.0f || bIsCharacterJumping) return;
    Stamina -= 0.2f;
    bIsCharacterJumping = true;
    ACharacter::Jump();
}

void AFPSPlayer::StopJumping()
{
    ACharacter::StopJumping();
}

void AFPSPlayer::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
    const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(ForwardVector, MovementVector.Y);
    AddMovementInput(RightVector, MovementVector.X);
}

void AFPSPlayer::StopMoving()
{
    if (bIsCharacterSprinting) {
        bIsCharacterSprinting = false;
        SetSpeedLimit(NormalSpeed);
    }
}

void AFPSPlayer::Lock(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();
    AddControllerPitchInput(MovementVector.Y * -1);
    AddControllerYawInput(MovementVector.X);

}

void AFPSPlayer::Fire()
{
}

void AFPSPlayer::SwitchViewMode()
{
    if (ThirdPersonCamera->IsActive()) {
        FPSCamera->SetActive(true);
        ThirdPersonCamera->SetActive(false);
    } else {
        FPSCamera->SetActive(false);
        ThirdPersonCamera->SetActive(true);
        FRotator CameraRotation = Player->GetControlRotation();
        CameraRotation.Pitch = 0.0f;
        Player->SetControlRotation(CameraRotation);
    }
}

void AFPSPlayer::Sprint()
{
    SetSpeedLimit(SprintSpeed);
    bIsCharacterSprinting = true;
}
void AFPSPlayer::StopSprinting() 
{
    SetSpeedLimit(NormalSpeed);
    bIsCharacterSprinting = false;
}

void AFPSPlayer::EndGame() 
{

    if (Player) {
        if (EndGameDelegate.IsBound()) {
            EndGameDelegate.Broadcast();
        }
        FRotator CameraRotation = Player->GetControlRotation();
        CameraRotation.Pitch -= 90.0f;
        Player->SetControlRotation(CameraRotation);
        FInputModeUIOnly InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        Player->bShowMouseCursor = true;
        Player->FlushPressedKeys();
        Player->SetInputMode(InputMode);
       if (!ThirdPersonCamera->IsActive()) {
            FPSCamera->SetActive(false);
            ThirdPersonCamera->SetActive(true);
       }
     }
}

void AFPSPlayer::ApplyDemage()
{
    Health -= 0.1f;
}
