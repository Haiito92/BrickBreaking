// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BRICKBREAKING_API UAudioGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitializeAudioSystem();	
	
	UFUNCTION(BlueprintCallable)
	void SwitchMusic(USoundBase* NewMusic, float FadeDuration = 2.0f);
	
private:
	UPROPERTY()
	TObjectPtr<UAudioComponent> MusicComponent;
	
	UPROPERTY()
	FGameplayTag AudioTag;
};
