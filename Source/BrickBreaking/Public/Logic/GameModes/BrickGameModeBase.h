// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BrickGameModeBase.generated.h"

class UUIEventHolder;
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
	
	UFUNCTION(BlueprintCallable)
	virtual void StartGame();
	UFUNCTION(BlueprintCallable)
	virtual void EndGame();
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUIEventHolder> UIEventHolder;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickPlayerControllerBase> PlayerController;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickHUDBase> HUD;
	
private:
	virtual bool InitializeGame();
	virtual bool InitializeUI();
	
	
	
	
	
};
