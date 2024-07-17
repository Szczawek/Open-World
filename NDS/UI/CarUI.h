// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CarUI.generated.h"

/**
 * 
 */
UCLASS()
class NDS_API UCarUI : public UUserWidget
{
	GENERATED_BODY()
	
protected: 
    virtual void NativeConstruct() override;

};
