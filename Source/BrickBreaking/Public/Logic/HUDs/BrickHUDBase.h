// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BrickHUDBase.generated.h"

class ABrickPlayerControllerBase;
class UUIEventHolder;
/**
 * 
 */
UCLASS()
class BRICKBREAKING_API ABrickHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual bool InitializeHUD(ABrickPlayerControllerBase* PlayerController, UUIEventHolder* InUIEventHolder);
	virtual void StartHUD();
	
protected:
	virtual bool InternalInitialize(ABrickPlayerControllerBase* PlayerController, UUIEventHolder* InUIEventHolder);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInternalInitialize(ABrickPlayerControllerBase* PlayerController, UUIEventHolder* InUIEventHolder);

	virtual bool CreateWidgets();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveCreateWidgets();
	
	virtual bool InitializeWidgets();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInitializeWidgets();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStartHUD();
private:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABrickPlayerControllerBase> PlayerController;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUIEventHolder> UIEventHolder;
};
