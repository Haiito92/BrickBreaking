// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "BrickGameViewportClient.generated.h"

class UDeviceGameInstanceSubsystem;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BRICKBREAKING_API UBrickGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
	virtual void Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice = true) override;
	
	virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;
	
	virtual bool InputAxis(const FInputKeyEventArgs& Args) override;
	
private:
	UPROPERTY()
	TObjectPtr<UDeviceGameInstanceSubsystem> DeviceSubsystem;
};
