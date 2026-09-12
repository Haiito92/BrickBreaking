// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameInstance/BrickGameInstance.h"

#include "Logic/Audio/AudioGameInstanceSubsystem.h"

void UBrickGameInstance::Init()
{
	Super::Init();
	
	UAudioGameInstanceSubsystem* AudioSystem = GetSubsystem<UAudioGameInstanceSubsystem>();
	
	if (IsValid(AudioSystem)) AudioSystem->InitializeAudioSystem();
}
