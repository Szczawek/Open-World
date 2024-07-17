// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include <Sound/SoundCue.h>
#include "Coin.generated.h"

UCLASS()
class NDS_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, Category = "Static Mesh")
    UStaticMeshComponent* Ball;
    UPROPERTY(EditAnywhere, Category="Ball Sphere")
    USphereComponent* CollisionSphere;

    UPROPERTY(EditAnywhere, Category = "Sound Effect")
    USoundCue* WalkInSound;

    UFUNCTION()
    void OnComponentBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
