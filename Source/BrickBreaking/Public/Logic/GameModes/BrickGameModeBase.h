// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BrickGameModeBase.generated.h"

class ABrickHUDBase;
class ABrickPlayerControllerBase;
/**
 * 
 */
UCLASS()
class BRICKBREAKING_API ABrickGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
private:
	virtual bool InitializeGame();
	virtual bool InitializeUI();
	
	UFUNCTION(BlueprintCallable)
	virtual void StartGame();
	UFUNCTION(BlueprintCallable)
	virtual void EndGame();
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickPlayerControllerBase> PlayerController;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickHUDBase> HUD;
	
	
};
