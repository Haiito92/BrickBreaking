// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickBreaking/Public/Logic/HUDs/BrickHUDBase.h"

#include "DebugLibrary.h"

bool ABrickHUDBase::InitializeHUD(ABrickPlayerControllerBase* PlayerController, UUIEventHolder* InUIEventHolder)
{
	if (!InternalInitialize(PlayerController, InUIEventHolder))
	{
		return false;
	}
	ReceiveInternalInitialize(PlayerController, InUIEventHolder);
	
	if (!CreateWidgets())
	{
		return false;
	}
	ReceiveCreateWidgets();
	
	if (!InitializeWidgets())
	{
		return false;
	}
	ReceiveInitializeWidgets();
	
	return true;
}

void ABrickHUDBase::StartHUD()
{
	ReceiveStartHUD();
}

bool ABrickHUDBase::InternalInitialize(ABrickPlayerControllerBase* PlayerController, UUIEventHolder* InUIEventHolder)
{
	UIEventHolder = InUIEventHolder;
	return true;
}

bool ABrickHUDBase::CreateWidgets()
{
	return true;
}

bool ABrickHUDBase::InitializeWidgets()
{
	return true;
}
