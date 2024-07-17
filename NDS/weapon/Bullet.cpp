// Fill out your copyright notice in the Description page of Project Settings.


#include "../weapon/Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MEST")); 
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    LifeTime += DeltaTime;
    if (LifeTime >= 7.0f) {
        this->Destroy();
    }
}