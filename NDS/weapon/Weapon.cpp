// Fill out your copyright notice in the Description page of Project Settings.


#include "../weapon/Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
    WeaponMesh->SetupAttachment(RootComponent);
   

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::FireBullet()
{
    UE_LOG(LogTemp, Warning, TEXT("SHOT"));
    if (BulletClass) {
    UE_LOG(LogTemp, Warning, TEXT("SHOT"));
    FVector SpawnLocation =  GetActorLocation(); // Example spawn location
    FRotator SpawnRotation = FRotator::ZeroRotator;

    FActorSpawnParameters SpawnParams;
    GetWorld()->SpawnActor<AActor>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);

    }
}



