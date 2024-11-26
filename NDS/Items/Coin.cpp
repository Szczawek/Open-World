// Fill out your copyright notice in the Description page of Project Settings.


#include "../Items/Coin.h"
#include "../Player/FPSPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Coin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
    RootComponent = CollisionSphere;
    Coin->SetupAttachment(CollisionSphere);


}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnComponentBeginOverLap);
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (bCoinIsColected) {
        if (Delta >= 3.0f) Destroy();
        FVector CurrentLocation = GetTargetLocation();
        CurrentLocation.Z += DeltaTime * 50.0f;
        this->SetActorLocation(CurrentLocation);
        Delta += DeltaTime;

    }

}

void ACoin::OnComponentBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AFPSPlayer* Character = Cast<AFPSPlayer>(OtherActor)) {
       if (WalkInSound) {
             UGameplayStatics::PlaySoundAtLocation(this, WalkInSound, GetActorLocation());
       }
       Character->AddPoint();
    }
    bCoinIsColected = true;
}

