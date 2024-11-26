// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Components/SphereComponent.h>
#include <Components/BoxComponent.h>
#include <InputMappingContext.h>
#include <InputAction.h>
#include "TreeCl.generated.h"

UCLASS()
class NDS_API ATreeCl : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATreeCl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, Category = "Inputs")
    UInputAction* ClimbAction;

    UPROPERTY(EditAnywhere, Category = "Inputs")
    UInputAction* HoldTreeAction;

    UPROPERTY(EditAnywhere, Category = "Inputs")
    UInputMappingContext* InputContext;

    UPROPERTY(EditAnywhere, Category = "Mesh")
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, Category = "Collision");
    USphereComponent* SphereCollision;

    UPROPERTY(EditAnywhere, Category = "Collison")
    UBoxComponent* BoxCollison;

    bool bIsCharacterInZone = false;
    bool bIsCharacterHoldTree = false;

    UFUNCTION()
    void HoldTree();

    UFUNCTION()
    void Climb(const FInputActionValue& Value);

    UFUNCTION()
    void OnOverlapZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SeepResult);

    UFUNCTION()
    void OnEndOverlapZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
};
