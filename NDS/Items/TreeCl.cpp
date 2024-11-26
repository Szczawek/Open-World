// Fill out your copyright notice in the Description page of Project Settings.


#include "../Items/TreeCl.h"
#include "EnhancedInputSubsystems.h"
#include <EnhancedInputComponent.h>
#include <NDS/Player/FPSPlayer.h>


// Sets default values
ATreeCl::ATreeCl()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    BoxCollison = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collison"));
    BoxCollison->SetupAttachment(Mesh);
    Mesh->SetupAttachment(SphereCollision);
    RootComponent = SphereCollision;
}

// Called when the game starts or when spawned
void ATreeCl::BeginPlay()
{
    Super::BeginPlay();
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
        if (UEnhancedInputLocalPlayerSubsystem* InputSystems = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
            InputSystems->AddMappingContext(InputContext, 0);
        }
    }
    BoxCollison->OnComponentBeginOverlap.AddDynamic(this, &ATreeCl::OnOverlapZone);
    BoxCollison->OnComponentEndOverlap.AddDynamic(this, &ATreeCl::OnEndOverlapZone);
}

// Called every frame
void ATreeCl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATreeCl::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("SDSD"));
        EnhancedInputComponent->BindAction(ClimbAction, ETriggerEvent::Triggered, this, &ATreeCl::Climb);
        EnhancedInputComponent->BindAction(HoldTreeAction, ETriggerEvent::Triggered, this, &ATreeCl::HoldTree);

    }
   
}

void ATreeCl::HoldTree()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("SDSSADASDASDD"));
    if (bIsCharacterHoldTree) {
        bIsCharacterHoldTree = false;
    }
}

void ATreeCl::Climb(const FInputActionValue& Value)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("12312321"));
    const FVector2D MovementVector = Value.Get<FVector2D>();
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
    const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
    AddMovementInput(ForwardVector, MovementVector.Y);
}

void ATreeCl::OnOverlapZone(UPrimitiveComponent* OverlapComponent, AActor* Actor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SeepResult)
{
    bIsCharacterInZone = true;
}

void ATreeCl::OnEndOverlapZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    bIsCharacterInZone = false;
}



