// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/GameModes/BrickGameModeBase.h"

#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"
#include "Kismet/GameplayStatics.h"
#include "Logic/GameEvents/GameEventHolder.h"
#include "Logic/GameEvents/UIEventHolder.h"
#include "Logic/HUDs/BrickHUDBase.h"
#include "Logic/Inputs/DeviceGameInstanceSubsystem.h"
#include "Logic/PlayerControllers/BrickPlayerControllerBase.h"

bool ABrickGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	if (!Super::SetPause(PC, CanUnpauseDelegate))
	{
		return false;
	}
	
	FInputModeGameAndUI InputModeGameAndUI ={};
	PlayerController->SetInputMode(InputModeGameAndUI);
	PlayerController->SetShowMouseCursor(true);
	
	GameEventHolder->LaunchEvent({EGameEventType::PauseStateChanged, true});
	
	return true;
}

bool ABrickGameModeBase::ClearPause()
{
	if (!Super::ClearPause())
	{
		return false;
	}
	
	FInputModeGameOnly InputModeGameOnly ={};
	PlayerController->SetInputMode(InputModeGameOnly);
	PlayerController->SetShowMouseCursor(false);
	
	GameEventHolder->LaunchEvent({EGameEventType::PauseStateChanged, false});
	
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

void ABrickGameModeBase::OnControlDeviceTypeChanged_Implementation(const EControlDeviceType& ControlDeviceType)
{
	ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Log,
		"[ABrickGameModeBase] GameMode reacts to control device change.", FColor::Magenta, 3.0f);
	
	switch (ControlDeviceType)
	{
	case EControlDeviceType::None:
		{
			return;
		}
	case EControlDeviceType::KeyboardAndMouse:
		{
			PlayerController->SetShowMouseCursor(true);
			return;
		}
	case EControlDeviceType::Gamepad:
		{
			PlayerController->SetShowMouseCursor(false);
			return;
		}
	}
}

bool ABrickGameModeBase::InitializeGame_Implementation()
{
	DeviceSystem = GetGameInstance()->GetSubsystem<UDeviceGameInstanceSubsystem>();
	
	if (!IsValid(DeviceSystem))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Warning,
			"[ABrickGameModeBase] Failed to get device subsystem!", FColor::Yellow, 3.0f);
	}
	else
	{
		DeviceSystem->ControlDeviceTypeChanged.AddDynamic(this, &ABrickGameModeBase::OnControlDeviceTypeChanged);	
	}
	
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

bool ABrickGameModeBase::EndGame_Implementation(bool Won)
{
	if (bGameEnded) return false;
	bGameEnded = true;
	return true;
}


void ABrickGameModeBase::OnPlayClicked_Implementation(const FUIEventInfo& EventInfo)
{
}

void ABrickGameModeBase::OnHomeClicked_Implementation(const FUIEventInfo& EventInfo)
{
}

void ABrickGameModeBase::OnPauseClicked_Implementation(const FUIEventInfo& EventInfo)
{
	if (bGameEnded) return;
	
	if (!IsValid(PlayerController))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickGameModeBase] Can't modify pause, invalid player controller!", FColor::Red, 3.0f);
		return;
	}
	
	if (IsPaused())
	{
		ClearPause();
		return;
	}
	
	SetPause(PlayerController);
}

void ABrickGameModeBase::OnQuitClicked_Implementation(const FUIEventInfo& EventInfo)
{
}
