// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "BrickGameModeBase.generated.h"

class UGameEventHolder;
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
	
	UFUNCTION(BlueprintNativeEvent)
	bool InitializeGame();
	UFUNCTION(BlueprintNativeEvent)
	bool InitializeUI();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartGame();
	
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndGame(bool Won);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnPlayClicked();
	UFUNCTION(BlueprintNativeEvent)
	void OnHomeClicked();
	UFUNCTION(BlueprintNativeEvent)
	void OnQuitClicked();
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag GameLoopTag;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUIEventHolder> UIEventHolder;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGameEventHolder> GameEventHolder;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickPlayerControllerBase> PlayerController;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickHUDBase> HUD;
	
	UPROPERTY(BlueprintReadWrite)
	bool bGameEnded;
};
