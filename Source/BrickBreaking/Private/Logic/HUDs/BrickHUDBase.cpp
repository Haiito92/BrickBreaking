// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/HUDs/BrickHUDBase.h"

#include "GameplayTagContainer.h"
#include "LittleDebugLibrary.h"
#include "MessageType.h"

bool ABrickHUDBase::InitializeHUD(ABrickPlayerControllerBase* InPlayerController, UUIEventHolder* InUIEventHolder, UGameEventHolder* InGameEventHolder)
{
	FGameplayTag GameLoopTag = FGameplayTag::RequestGameplayTag("GameLoop");
	if (!InternalInitialize(InPlayerController, InUIEventHolder, InGameEventHolder))
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickHUDBase] Failed internal init!", FColor::Red, 3.0f);
		return false;
	}
	ReceiveInternalInitialize(InPlayerController, InUIEventHolder, InGameEventHolder);
	
	if (!CreateWidgets())
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickHUDBase] Failed create widgets!", FColor::Red, 3.0f);
		return false;
	}
	ReceiveCreateWidgets();
	
	if (!InitializeWidgets())
	{
		ULittleDebugLibrary::AddOnScreenDebugMessage(GameLoopTag, EDebugMessageType::Error,
			"[ABrickHUDBase] Failed init widgets!", FColor::Red, 3.0f);
		return false;
	}
	ReceiveInitializeWidgets();
	
	return true;
}

void ABrickHUDBase::StartHUD()
{
	ReceiveStartHUD();
}

bool ABrickHUDBase::InternalInitialize_Implementation(ABrickPlayerControllerBase* InPlayerController, UUIEventHolder* InUIEventHolder, UGameEventHolder* InGameEventHolder)
{
	UIEventHolder = InUIEventHolder;
	GameEventHolder = InGameEventHolder;
	return true;
}

bool ABrickHUDBase::CreateWidgets_Implementation()
{
	return true;
}

bool ABrickHUDBase::InitializeWidgets_Implementation()
{
	return true;
}
