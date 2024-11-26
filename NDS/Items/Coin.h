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
	ACoin();

protected:
	virtual void BeginPlay() override;

public:	
    virtual void Tick(float DeltaTime) override;

    bool bCoinIsColected = false;
    float Delta = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Mesh")
    UStaticMeshComponent* Coin;

    UPROPERTY(EditAnywhere, Category="Sphere Collision")
    USphereComponent* CollisionSphere;

    UPROPERTY(EditAnywhere, Category = "Sound Effect")
    USoundCue* WalkInSound;

    UFUNCTION()
    void OnComponentBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
