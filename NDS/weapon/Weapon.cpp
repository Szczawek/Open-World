// Fill out your copyright notice in the Description page of Project Settings.


#include "../weapon/Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere collision"));
    RootComponent = SphereCollision;
    SphereCollision->SetSphereRadius(50.0f);
    Mesh->SetupAttachment(SphereCollision);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
    SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnCharacterOverlap);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (!bIsWeaponTaken) {
        FRotator Rotation = this->GetActorRotation();
        Rotation.Yaw += DeltaTime * 40.0f;
        SetActorRotation(Rotation);
    }

}

void AWeapon::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AFPSPlayer* PlayerCharacter = Cast<AFPSPlayer>(OtherActor)) {
        PlayerCharacter->PlayerHoldWeapon();
        FName HandSocketName = TEXT("hand_l"); 
        AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocketName);
        SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        bIsWeaponTaken = true;
    }
}



