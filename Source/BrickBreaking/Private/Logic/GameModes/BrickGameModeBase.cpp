// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameModes/BrickGameModeBase.h"

#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Kismet/GameplayStatics.h"
#include "Logic/GameEvents/GameEventHolder.h"
#include "Logic/GameEvents/UIEventHolder.h"
#include "Logic/HUDs/BrickHUDBase.h"
#include "Logic/PlayerControllers/BrickPlayerControllerBase.h"

void ABrickGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GameLoopTag = FGameplayTag::RequestGameplayTag("GameLoop");
	
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

bool ABrickGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	if (!Super::SetPause(PC, CanUnpauseDelegate))
	{
		return false;
	}
	
	bool bIsPaused = IsPaused();
	if (bIsPaused)
	{
		// Change input mode	
		// Change imc	
	}
	else
	{
		// Change input mode	
		// Change imc	
	}
	
	GameEventHolder->LaunchEvent({EGameEventType::PauseStateChanged, bIsPaused});
	
	return true;
}

bool ABrickGameModeBase::InitializeGame_Implementation()
{
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
	
	UIEventHolder->PlayClicked.AddDynamic(this, &ABrickGameModeBase::OnPlayClicked);
	UIEventHolder->HomeClicked.AddDynamic(this, &ABrickGameModeBase::OnHomeClicked);
	UIEventHolder->QuitClicked.AddDynamic(this, &ABrickGameModeBase::OnQuitClicked);
	
	GameEventHolder = NewObject<UGameEventHolder>(this);
	if (!IsValid(GameEventHolder))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Failed to create UIEventHolder!", FColor::Red, 3.0f);
		return false;
	}
	
	bGameEnded = false;
	
	return true;
}

bool ABrickGameModeBase::InitializeUI_Implementation()
{
	HUD = Cast<ABrickHUDBase>(PlayerController->GetHUD());
	if (!IsValid(HUD))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Failed to get HUD!", FColor::Red, 3.0f);
		return false;
	}
	
	if (!HUD->InitializeHUD(PlayerController, UIEventHolder, GameEventHolder))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Failed to init HUD!", FColor::Red, 3.0f);
		return false;
	}
	
	return true;
}

void ABrickGameModeBase::StartGame_Implementation()
{
}

void ABrickGameModeBase::EndGame_Implementation(bool Won)
{
	if (bGameEnded) return;
}

void ABrickGameModeBase::OnPlayClicked_Implementation()
{
}


void ABrickGameModeBase::OnHomeClicked_Implementation()
{
}

void ABrickGameModeBase::OnQuitClicked_Implementation()
{
}
