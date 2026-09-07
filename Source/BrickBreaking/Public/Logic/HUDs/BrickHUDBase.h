// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BrickHUDBase.generated.h"

class ABrickPlayerControllerBase;
class UUIEventHolder;
class UGameEventHolder;
/**
 * 
 */
UCLASS()
class BRICKBREAKING_API ABrickHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual bool InitializeHUD(ABrickPlayerControllerBase* InPlayerController, UUIEventHolder* InUIEventHolder, UGameEventHolder* InGameEventHolder);
	virtual void StartHUD();
	
protected:
	UFUNCTION(BlueprintNativeEvent)
	bool InternalInitialize(ABrickPlayerControllerBase* InPlayerController, UUIEventHolder* InUIEventHolder, UGameEventHolder* InGameEventHolder);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInternalInitialize(ABrickPlayerControllerBase* InPlayerController, UUIEventHolder* InUIEventHolder, UGameEventHolder* InGameEventHolder);

	UFUNCTION(BlueprintNativeEvent)
	bool CreateWidgets();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveCreateWidgets();
	
	UFUNCTION(BlueprintNativeEvent)
	bool InitializeWidgets();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInitializeWidgets();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStartHUD();
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickPlayerControllerBase> PlayerController;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUIEventHolder> UIEventHolder;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGameEventHolder> GameEventHolder;
};
