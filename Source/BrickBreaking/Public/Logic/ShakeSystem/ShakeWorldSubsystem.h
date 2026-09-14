// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual TStatId GetStatId() const override;
	
	UFUNCTION(BlueprintCallable)
	bool InitializeShakeSystem();
	
	UFUNCTION(BlueprintCallable)
	void LaunchShake(float ShakeStrength);
	
private:
	FGameplayTag ShakeTag;
	
	UPROPERTY()
	TArray<TObjectPtr<UShakeableComponent>> Shakeables;
};
