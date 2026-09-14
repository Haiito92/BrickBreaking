// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameInstance/BrickGameInstance.h"

#include "Framework/Application/NavigationConfig.h"
#include "Logic/Audio/AudioGameInstanceSubsystem.h"

void UBrickGameInstance::Init()
{
	Super::Init();
	
	UAudioGameInstanceSubsystem* AudioSystem = GetSubsystem<UAudioGameInstanceSubsystem>();
	
	if (IsValid(AudioSystem)) AudioSystem->InitializeAudioSystem();
	
	
	TSharedPtr<FNavigationConfig> NavConfig = FSlateApplication::Get().GetNavigationConfig();
	if (NavConfig.IsValid())
	{
		NavConfig->KeyEventRules.Add(EKeys::W, EUINavigation::Up);
		NavConfig->KeyEventRules.Add(EKeys::S, EUINavigation::Down);
		NavConfig->KeyEventRules.Add(EKeys::A, EUINavigation::Left);
		NavConfig->KeyEventRules.Add(EKeys::D, EUINavigation::Right);
	}
}
