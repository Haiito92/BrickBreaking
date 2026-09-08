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

bool ABrickGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	if (!Super::SetPause(PC, CanUnpauseDelegate))
	{
		return false;
	}
	
	bool bIsPaused = IsPaused();
	if (bIsPaused)
	{
		FInputModeGameAndUI InputModeGameAndUI ={};
		PlayerController->SetInputMode(InputModeGameAndUI);
		PlayerController->SetShowMouseCursor(true);
	}
	else
	{
		FInputModeGameOnly InputModeGameOnly ={};
		PlayerController->SetInputMode(InputModeGameOnly);
		PlayerController->SetShowMouseCursor(true);
	}
	
	GameEventHolder->LaunchEvent({EGameEventType::PauseStateChanged, bIsPaused});
	
	return true;
}

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
	UIEventHolder->PauseClicked.AddDynamic(this, &ABrickGameModeBase::OnPauseClicked);
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


void ABrickGameModeBase::OnPlayClicked_Implementation(const FUIEventInfo& EventInfo)
{
}


void ABrickGameModeBase::OnHomeClicked_Implementation(const FUIEventInfo& EventInfo)
{
}


void ABrickGameModeBase::OnPauseClicked_Implementation(const FUIEventInfo& EventInfo)
{
}

void ABrickGameModeBase::OnQuitClicked_Implementation(const FUIEventInfo& EventInfo)
{
}
