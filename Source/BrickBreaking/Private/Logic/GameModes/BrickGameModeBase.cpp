// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameModes/BrickGameModeBase.h"

#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Kismet/GameplayStatics.h"
#include "Logic/GameEvents/UIEventHolder.h"
#include "Logic/HUDs/BrickHUDBase.h"
#include "Logic/PlayerControllers/BrickPlayerControllerBase.h"

void ABrickGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	FGameplayTag GameLoopTag = FGameplayTag::RequestGameplayTag("GameLoop");
	
	if (!InitializeGame())
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Failed init game!", FColor::Red, 3.0f);
		return;
	}
	
	if (!InitializeUI())
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Failed init UI!", FColor::Red, 3.0f);
		return;
	}
	
	StartGame();
}

bool ABrickGameModeBase::InitializeGame()
{
	FGameplayTag GameLoopTag = FGameplayTag::RequestGameplayTag("GameLoop");
	
	PlayerController = Cast<ABrickPlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	if (!IsValid(PlayerController))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Failed to get player controller!", FColor::Red, 3.0f);
		return false;
	}
	
	UIEventHolder = NewObject<UUIEventHolder>(this);
	if (!IsValid(UIEventHolder))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Failed to create UIEventHolder!", FColor::Red, 3.0f);
		return false;
	}
	
	return true;
}

bool ABrickGameModeBase::InitializeUI()
{
	FGameplayTag GameLoopTag = FGameplayTag::RequestGameplayTag("GameLoop");
	
	HUD = Cast<ABrickHUDBase>(PlayerController->GetHUD());
	if (!IsValid(HUD))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Failed to get HUD!", FColor::Red, 3.0f);
		return false;
	}
	
	if (!HUD->InitializeHUD(PlayerController, UIEventHolder))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Failed to init HUD!", FColor::Red, 3.0f);
		return false;
	}
	
	return true;
}

void ABrickGameModeBase::StartGame()
{
}

void ABrickGameModeBase::EndGame()
{
}
