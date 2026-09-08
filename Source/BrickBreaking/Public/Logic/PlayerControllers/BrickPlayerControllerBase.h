// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "BrickPlayerControllerBase.generated.h"

class UInputAction;
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
	
	UFUNCTION(BlueprintNativeEvent)
	void OnPauseActionStarted(const FInputActionValue& InputActionValue);
	
	UPROPERTY(EditAnywhere, Category="Input|Input Mapping Contexts")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	
	UPROPERTY(EditAnywhere, Category="Input|Input Actions")
	TObjectPtr<UInputAction> PauseAction;
};
