// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DeviceGameInstanceSubsystem.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EControlDeviceType: uint8
{
	None,
	KeyboardAndMouse,
	Gamepad,
};

UCLASS()
class BRICKBREAKING_API UDeviceGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	bool InitializeDeviceSubsystem();
	
	UFUNCTION(BlueprintCallable)
	const EControlDeviceType& GetCurrentControlDeviceType() const;
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentControlDeviceType(const EControlDeviceType& InControlDeviceType);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FControlDeviceTypeChangedSignature, const EControlDeviceType&, ControlDeviceType);
	UPROPERTY(BlueprintAssignable)
	FControlDeviceTypeChangedSignature ControlDeviceTypeChanged;
private:
	UPROPERTY()
	EControlDeviceType CurrentControlDeviceType;
};
