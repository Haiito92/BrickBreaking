// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Inputs/DeviceGameInstanceSubsystem.h"

bool UDeviceGameInstanceSubsystem::InitializeDeviceSubsystem()
{
	return true;
}

const EControlDeviceType& UDeviceGameInstanceSubsystem::GetCurrentControlDeviceType() const
{
	return CurrentControlDeviceType;
}

void UDeviceGameInstanceSubsystem::SetCurrentControlDeviceType(const EControlDeviceType& InControlDeviceType)
{
	if (InControlDeviceType == EControlDeviceType::None || InControlDeviceType == CurrentControlDeviceType) return;
	
	CurrentControlDeviceType = InControlDeviceType;
	
	ControlDeviceTypeChanged.Broadcast(CurrentControlDeviceType);
}
