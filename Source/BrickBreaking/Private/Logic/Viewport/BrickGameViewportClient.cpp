// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Viewport/BrickGameViewportClient.h"

#include "Logic/Inputs/DeviceGameInstanceSubsystem.h"

void UBrickGameViewportClient::Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance,
                                    bool bCreateNewAudioDevice)
{
	Super::Init(WorldContext, OwningGameInstance, bCreateNewAudioDevice);
	
	DeviceSubsystem = GetGameInstance()->GetSubsystem<UDeviceGameInstanceSubsystem>();
}

bool UBrickGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	EControlDeviceType NewControlDeviceType = EControlDeviceType::KeyboardAndMouse;
	
	if (EventArgs.IsGamepad())
	{
		NewControlDeviceType = EControlDeviceType::Gamepad;
	}
	
	if (IsValid(DeviceSubsystem)) DeviceSubsystem->SetCurrentControlDeviceType(NewControlDeviceType);
	
	return Super::InputKey(EventArgs);
}

bool UBrickGameViewportClient::InputAxis(const FInputKeyEventArgs& Args)
{
	EControlDeviceType NewControlDeviceType = EControlDeviceType::KeyboardAndMouse;
	
	if (Args.IsGamepad())
	{
		NewControlDeviceType = EControlDeviceType::Gamepad;
	}
	
	if (IsValid(DeviceSubsystem)) DeviceSubsystem->SetCurrentControlDeviceType(NewControlDeviceType);
	
	return Super::InputAxis(Args);
}
