// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "../Player/FPSPlayer.h"
#include "Weapon.generated.h"

UCLASS()
class NDS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY()
    bool bIsWeaponTaken = false;

    UPROPERTY(EditAnyWhere, Category = "Mesh");
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, Category = "Sphere Collision")
    USphereComponent* SphereCollision;
    
    UFUNCTION()
    void OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
