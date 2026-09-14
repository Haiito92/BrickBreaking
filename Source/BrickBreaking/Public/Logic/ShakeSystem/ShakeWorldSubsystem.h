// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ShakeWorldSubsystem.generated.h"

class UShakeableComponent;
/**
 * 
 */
UCLASS()
class BRICKBREAKING_API UShakeWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool InitializeShakeSystem();
	
	UFUNCTION(BlueprintCallable)
	void LaunchShake(float ShakeStrength);
	
private:
	UPROPERTY()
	TArray<TObjectPtr<UShakeableComponent>> Shakeables;
};
