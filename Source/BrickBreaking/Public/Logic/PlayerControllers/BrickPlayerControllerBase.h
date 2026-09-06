// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BrickPlayerControllerBase.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class BRICKBREAKING_API ABrickPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, Category="Input|Input Mapping Contexts")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
};
