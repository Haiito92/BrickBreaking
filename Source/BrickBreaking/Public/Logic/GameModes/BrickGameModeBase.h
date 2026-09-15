// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "Logic/Inputs/DeviceGameInstanceSubsystem.h"
#include "BrickGameModeBase.generated.h"

class UDeviceGameInstanceSubsystem;
struct FUIEventInfo;
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
public:
	
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;
	

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent)
	bool InitializeGame();
	UFUNCTION(BlueprintNativeEvent)
	bool InitializeUI();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartGame();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool EndGame(bool Won);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnPlayClicked(const FUIEventInfo& EventInfo);
	UFUNCTION(BlueprintNativeEvent)
	void OnHomeClicked(const FUIEventInfo& EventInfo);
	UFUNCTION(BlueprintNativeEvent)
	void OnPauseClicked(const FUIEventInfo& EventInfo);
	UFUNCTION(BlueprintNativeEvent)
	void OnQuitClicked(const FUIEventInfo& EventInfo);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnControlDeviceTypeChanged(const EControlDeviceType& ControlDeviceType);
	
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
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDeviceGameInstanceSubsystem> DeviceSystem;
	
	UPROPERTY(BlueprintReadWrite)
	bool bGameEnded;
};
